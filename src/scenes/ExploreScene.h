#pragma once

#include <MoveComponent.h>
#include "RogueFortScene.h"
#include "../components/MoveComponentWithCollision.h"

class Camera;


class Collider;
class ActionMenu;

class ExploreScene : public RogueFortScene {
public:
    ExploreScene(Camera* camera);
    virtual Camera* getCamera();
    virtual void update(float dt, std::vector<std::shared_ptr<GameObject>> &toDelete);
    virtual void resize(int x, int y);

    virtual void sceneEntry(Player* player, Camera *camera);

private:
    void createLight();
    Camera* camera;
    std::shared_ptr<GameObject> player;
    MoveComponentWithCollision *moveComponent;
    Collider *collider;

};
