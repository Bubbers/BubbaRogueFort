#pragma once

#include <memory>
#include <Camera.h>
#include <Scene.h>
#include "logic/Player.h"

class Scene;
class Camera;
class GameObject;

class RogueFortScene{
public:
    virtual void requestSceneChange(std::string newSceneName);
    virtual bool changeScene();
    void setShouldChangeScene(bool newValue);

    virtual void sceneEntry(Player* player, Camera *camera) {};
    virtual void sceneExit(Player* player , Camera *camera)  {};

    virtual void resize(int x, int y){}
    virtual void update(float dt, std::vector<std::shared_ptr<GameObject>> &toDelete);

    virtual Scene* getScene();
    virtual Camera* getCamera();

    std::string getNewSceneName();

protected:
    Scene* scene;
    Camera* camera;

    std::string newSceneName;
    bool shouldChangeScene = false;
};
