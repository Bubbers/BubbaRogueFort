//
// Created by johan on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_SCENESWITCHONCOLLISIONCOMPONENT_H
#define BUBBAROGUEFORT_SCENESWITCHONCOLLISIONCOMPONENT_H


#include <IComponent.h>
#include <Scene.h>
#include <Collider.h>
#include "../scenes/RogueFortScene.h"

class SceneSwitchOnCollisionComponent : public IComponent{
public:
    SceneSwitchOnCollisionComponent(RogueFortScene *scene, std::string newSceneName);

    void update(float dt);
    virtual void beforeCollision(GameObject* collider) override ;
private:
    RogueFortScene *scene;
    std::string newSceneName;
};


#endif //BUBBAROGUEFORT_SCENESWITCHONCOLLISIONCOMPONENT_H
