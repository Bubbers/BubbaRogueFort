//
// Created by simon on 2016-06-21.
//

#include <PerspectiveCamera.h>
#include <ResourceManager.h>
#include <constants.h>
#include <StandardRenderer.h>
#include <Globals.h>
#include <ControlsManager.h>
#include <KeyboardButton.h>
#include "ExploreScene.h"
#include "ColliderFactory.h"
#include "../components/PlayerCamera.h"
#include "../controls.h"
#include "../ui/ActionMenu.h"
#include "../level/LevelFileReader.h"


float3 UP_VECTOR = make_vector(0.0f,1.0f,0.0f);

ExploreScene::ExploreScene() : RogueFortScene() {

    scene = LevelFileReader::read("../levels/test.level", this);
    collider = ColliderFactory::getTwoPhaseCollider();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);

    /* Shader setup done once for all meshes that use it */
    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/monkey.obj");
    // references are from the the build folder

    // character to move
    player = new GameObject(playerMesh);
    moveComponent = new MoveComponentWithCollision(player);
    player->addComponent(moveComponent);

    player->setLocation(make_vector(0.0f, 0.2f,0.0f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);
    player->setIdentifier(0);
    player->addCollidesWith(1);

    /* Add the player to the scene */
    scene->addShadowCaster(player);

    player->addComponent(camera);

    GameObject* hudObj = new GameObject();
    hud = new ActionMenu();
    hudObj->addRenderComponent(hud);
    scene->addTransparentObject(hudObj);

    createLight();
}

void ExploreScene::createLight() {

    DirectionalLight directionalLight = DirectionalLight();
    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.50f,0.50f,0.50f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);
    scene->directionalLight = directionalLight;

    PointLight pointLight;
    pointLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    pointLight.specularColor=make_vector(0.00f,0.00f,0.00f);
    pointLight.ambientColor=make_vector(0.050f,0.050f,0.050f);
    pointLight.position = make_vector(18.0f, 3.0f, 0.0f);
    scene->pointLights.push_back(pointLight);
}

void ExploreScene::resize(int x, int y) {
    hud->updateLayout();
}

Camera* ExploreScene::getCamera() {
    return camera;
}


void ExploreScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    collider->updateCollision(scene);
}

