#include "SceneSwitchOnCollisionComponent.h"

SceneSwitchOnCollisionComponent::SceneSwitchOnCollisionComponent(RogueFortScene *scene, std::string newSceneName) {
    this->scene = scene;
    this->newSceneName = newSceneName;
}

void SceneSwitchOnCollisionComponent::beforeCollision(std::shared_ptr<GameObject> collider) {
    scene->requestSceneChange(newSceneName);
}

void SceneSwitchOnCollisionComponent::update(float dt) {

}
