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

float3 UP_VECTOR = make_vector(0.0f,1.0f,0.0f);

ExploreScene::ExploreScene() : RogueFortScene() {

    collider = ColliderFactory::getTwoPhaseCollider();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 10.0f, 10.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);

    /* Shader setup done once for all meshes that use it */
    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/player.fbx");
    // references are from the the build folder


    // character to move
    player = new GameObject(playerMesh);
    moveComponent = new MoveComponentWithCollision(player);
    player->addComponent(moveComponent);

    player->setLocation(make_vector(0.0f, 0.0f,0.0f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);
    player->setIdentifier(0);
    player->addCollidesWith(1);

    /* Add the player to the scene */
    addShadowCaster(player);

    player->addComponent(camera);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *FloorMesh = ResourceManager::loadAndFetchMesh("../meshes/ground.obj");
    // references are from the the build folder


    GameObject* floor = new GameObject(FloorMesh);
    floor->setLocation(make_vector(5.0f, 0.0f,0.0f));
    StandardRenderer *floorrenderer = new StandardRenderer(FloorMesh, floor, standardShader);
    floor->addRenderComponent(floorrenderer);
    floor->setDynamic(true);
    floor->setIdentifier(1);

    /* Add the player to the scene */
    addShadowCaster(floor);

    createLight();
}

void ExploreScene::createLight() {

    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.50f,0.50f,0.50f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);
}

Camera* ExploreScene::getCamera() {
    return camera;
}

bool ExploreScene::changeScene() {
    return false;
}

void ExploreScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    collider->updateCollision(this);
}

