//
// Created by johan on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_BATTLESCENE_H
#define BUBBAROGUEFORT_BATTLESCENE_H


#include "RogueFortScene.h"

class BattleScene : public RogueFortScene {
public:
    BattleScene();

    virtual Camera* getCamera();
    virtual void update(float dt, std::vector<GameObject*> *toDelete);
    virtual void resize(int x, int y);

private:

    void createLight();

    Camera* camera;
};


#endif //BUBBAROGUEFORT_BATTLESCENE_H
