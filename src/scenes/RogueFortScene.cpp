#include "RogueFortScene.h"
#include <memory>

Scene* RogueFortScene::getScene() {
    return scene;
}

Camera* RogueFortScene::getCamera() {
    return camera;
}

void RogueFortScene::update(float dt, std::vector<std::shared_ptr<GameObject>> &toDelete) {
    scene->update(dt, &toDelete);
}

std::string RogueFortScene::getNewSceneName() {
    return newSceneName;
}

bool RogueFortScene::changeScene() {
    return shouldChangeScene;
}

void RogueFortScene::requestSceneChange(std::string newSceneName) {
    shouldChangeScene = true;
    this->newSceneName = newSceneName;
}

void RogueFortScene::setShouldChangeScene(bool newValue) {
    shouldChangeScene = newValue;
}

