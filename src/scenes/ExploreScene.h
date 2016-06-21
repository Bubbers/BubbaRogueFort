//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_EXPLORESCENE_H
#define BUBBAROGUEFORT_EXPLORESCENE_H


#include <MoveComponent.h>
#include "RogueFortScene.h"
#include "../components/MoveComponentWithCollision.h"

class Camera;


class Collider;

class ExploreScene : public RogueFortScene {
public:
    ExploreScene();
    virtual Camera* getCamera();
    virtual bool changeScene();
    virtual void update(float dt, std::vector<GameObject*> *toDelete);

private:
    void createLight();
    void initKeyBindings();
    void checkKeyboardKeys();
    Camera* camera;
    GameObject* player;
    MoveComponentWithCollision *moveComponent;
    Collider *collider;
};


#endif //BUBBAROGUEFORT_EXPLORESCENE_H
