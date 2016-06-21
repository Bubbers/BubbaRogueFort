//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_STARTSCENE_H
#define BUBBAROGUEFORT_STARTSCENE_H

#include "Scene.h"
#include "RogueFortScene.h"
#include "../IdentityCamera.h"

class Layout;
class Font;
class HudRenderer;

class StartScene : public RogueFortScene {
public:
    StartScene();
    virtual Camera* getCamera();
    virtual bool changeScene();
    virtual void resize(int x, int y);

private:
    Layout* createMenu();
    Font* titleFont;
    Font* playFont;
    HudRenderer* hudRenderer;
    bool playIsClicked = false;
    Camera* camera = new IdentityCamera();
    static void hoverPlay(int x, int y, Layout* hoveringOn, bool enteringElseLeaving);
    void clickPlay(int x, int y, Layout* clickedOn,bool enteringElseLeaving);
};


#endif //BUBBAROGUEFORT_STARTSCENE_H
