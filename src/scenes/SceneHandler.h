//
// Created by johan on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_SCENEHANDLER_H
#define BUBBAROGUEFORT_SCENEHANDLER_H


#include "RogueFortScene.h"

class SceneHandler {
public:
    SceneHandler(Player* player, Camera* camera);

    void idle(float timeSinceStart,float timeSinceLastCall);

    RogueFortScene* getCurrentScene();
    void resize(int newWidth, int newHeight);

private:
    RogueFortScene* scene;
    RogueFortScene *startScene;
    RogueFortScene *explorerScene;

    Player *player;
    Camera *camera;

};


#endif //BUBBAROGUEFORT_SCENEHANDLER_H
