//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_ROGUEFORTSCENE_H
#define BUBBAROGUEFORT_ROGUEFORTSCENE_H


#include <Camera.h>
#include <Scene.h>

class Scene;
class Camera;
class GameObject;

class RogueFortScene{
public:
    virtual bool changeScene() = 0;
    virtual void resize(int x, int y){}
    virtual void update(float dt, std::vector<GameObject*>* toDelete);

    virtual Scene* getScene();
    virtual Camera* getCamera();

protected:
    Scene* scene;
    Camera* camera;
};


#endif //BUBBAROGUEFORT_ROGUEFORTSCENE_H
