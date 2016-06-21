//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_ROGUEFORTSCENE_H
#define BUBBAROGUEFORT_ROGUEFORTSCENE_H


#include <Camera.h>
#include <Scene.h>

class RogueFortScene : public Scene{
public:
    virtual Camera* getCamera() = 0;
    virtual bool changeScene() = 0;
    virtual void resize(int x, int y){}
};


#endif //BUBBAROGUEFORT_ROGUEFORTSCENE_H
