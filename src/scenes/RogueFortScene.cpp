//
// Created by simon on 2016-06-21.
//

#include "RogueFortScene.h"

Scene* RogueFortScene::getScene() {
    return scene;
}

Camera* RogueFortScene::getCamera() {
    return camera;
}

void RogueFortScene::update(float dt, std::vector<GameObject *>* toDelete) {
    scene->update(dt,toDelete);
}