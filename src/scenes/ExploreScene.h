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
class ActionMenu;

class ExploreScene : public RogueFortScene {
public:
    ExploreScene();
    virtual Camera* getCamera();
    virtual void update(float dt, std::vector<GameObject*> *toDelete);
    virtual void resize(int x, int y);

    virtual void sceneEntry(GameObject* player, Camera *camera);
    virtual void sceneExit(GameObject* player, Camera *camera) ;

private:
    void createLight();
    Camera* camera;
    GameObject* player;
    MoveComponentWithCollision *moveComponent;
    Collider *collider;

};


#endif //BUBBAROGUEFORT_EXPLORESCENE_H
