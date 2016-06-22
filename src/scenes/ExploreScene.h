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
    virtual void update(float dt, std::vector<GameObject*> *toDelete);
    virtual void resize(int x, int y);

private:
    void createLight();
    Camera* camera;
    GameObject* player;
    MoveComponentWithCollision *moveComponent;
    Collider *collider;
    HudRenderer *hud;
};


#endif //BUBBAROGUEFORT_EXPLORESCENE_H
