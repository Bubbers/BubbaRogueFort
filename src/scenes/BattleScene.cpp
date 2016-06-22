//
// Created by johan on 2016-06-22.
//

#include <Globals.h>
#include "BattleScene.h"
#include "../level/LevelFileReader.h"
#include "../components/PlayerCamera.h"


BattleScene::BattleScene() {
    scene = LevelFileReader::read("../levels/battle.level", this);

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);
    createLight();
}

void BattleScene::createLight() {

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


void BattleScene::resize(int x, int y) {
}

Camera* BattleScene::getCamera() {
    return camera;
}


void BattleScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
}
