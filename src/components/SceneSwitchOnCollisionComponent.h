#pragma once

#include <memory>

#include <IComponent.h>
#include <Scene.h>
#include <Collider.h>
#include "scenes/RogueFortScene.h"

class SceneSwitchOnCollisionComponent : public IComponent{
public:
    SceneSwitchOnCollisionComponent(RogueFortScene *scene, std::string newSceneName);

    void update(float dt) override;
    virtual void beforeCollision(std::shared_ptr<GameObject> collider) override ;
private:
    RogueFortScene *scene;
    std::string newSceneName;
};
