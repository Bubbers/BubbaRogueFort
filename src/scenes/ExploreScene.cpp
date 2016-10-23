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
#include "../logic/KidBandit.h"


using namespace chag;
float3 UP_VECTOR = chag::make_vector(0.0f,1.0f,0.0f);


ExploreScene::ExploreScene(Camera* camera) : RogueFortScene() {

    scene = LevelFileReader::read("../levels/test.level", this);
    collider = ColliderFactory::getTwoPhaseCollider();
    this->camera = camera;

    /* Shader setup done once for all meshes that use it */
    std::shared_ptr<ShaderProgram> standardShader = ResourceManager::loadAndFetchShaderProgram(SIMPLE_SHADER_NAME, "../shader/simple.vert", "../shader/simple.frag");

    /* Load player mesh and attach it to the player GameObject */
    std::shared_ptr<Mesh> playerMesh = ResourceManager::loadAndFetchMesh("../meshes/bubba.obj");
    // references are from the the build folder

    // character to move
    player = new GameObject(playerMesh);
    MoveComponentWithCollision *moveComponent = new MoveComponentWithCollision(player);
    player->addComponent(moveComponent);

    player->setLocation(make_vector(0.0f, 0.2f,0.0f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);
    player->setIdentifier(0);
    player->addCollidesWith(1);

    player->addComponent(camera);
    scene->addShadowCaster(player);

    createLight();
}

void ExploreScene::createLight() {

    DirectionalLight directionalLight = DirectionalLight();
    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.0050f,0.0050f,0.0050f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);
    scene->directionalLight = directionalLight;

    PointLight pointLight;
    pointLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    pointLight.specularColor=make_vector(0.00f,0.00f,0.00f);
    pointLight.ambientColor=make_vector(0.00050f,0.00050f,0.00050f);
    pointLight.position = make_vector(18.0f, 3.0f, 0.0f);
    scene->pointLights.push_back(pointLight);
}

void ExploreScene::resize(int x, int y) {

}

Camera* ExploreScene::getCamera() {
    return camera;
}


void ExploreScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    collider->updateCollision(scene);


}

void ExploreScene::sceneEntry(Player* player, Camera *camera) {
    this->camera = camera;
}
