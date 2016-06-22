//
// Created by johan on 2016-06-22.
//

#include "SceneSwitchOnCollisionComponent.h"

SceneSwitchOnCollisionComponent::SceneSwitchOnCollisionComponent(RogueFortScene *scene, std::string newSceneName) {
    this->scene = scene;
    this->newSceneName = newSceneName;
}

void SceneSwitchOnCollisionComponent::beforeCollision(GameObject* collider) {
    scene->requestSceneChange(newSceneName);
}

void SceneSwitchOnCollisionComponent::update(float dt) {

}