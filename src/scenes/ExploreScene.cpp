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
#include "../logic/KidBandit.h"


float3 UP_VECTOR = make_vector(0.0f,1.0f,0.0f);

ExploreScene::ExploreScene() : RogueFortScene() {

    scene = LevelFileReader::read("../levels/test.level", this);
    collider = ColliderFactory::getTwoPhaseCollider();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);

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

}

Camera* ExploreScene::getCamera() {
    return camera;
}


void ExploreScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    collider->updateCollision(scene);


}

void ExploreScene::sceneEntry(GameObject* player, Camera *camera) {
    scene->addShadowCaster(player);
    this->camera = camera;
}

void ExploreScene::sceneExit(GameObject* player, Camera *camera)  {

}