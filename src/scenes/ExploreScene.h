//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_EXPLORESCENE_H
#define BUBBAROGUEFORT_EXPLORESCENE_H


#include "RogueFortScene.h"

class Camera;

class ExploreScene : public RogueFortScene {
public:
    ExploreScene();
    virtual Camera* getCamera();
    virtual bool changeScene();

private:
    Camera* camera;
    GameObject* player;
};


#endif //BUBBAROGUEFORT_EXPLORESCENE_H
