//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_ACTIONMENU_H
#define BUBBAROGUEFORT_ACTIONMENU_H


#include <HudRenderer.h>
#include <Layout.h>

class Font;

class ActionMenu : public HudRenderer {
public:
    ActionMenu();

private:
    Layout* createActionButton(std::string name);
    Font* font;
    static void onActionHover(int x, int y, Layout* hoveredOn, bool enteredElseLeaving);
    static void onActionClick(int x, int y, Layout* clickedOn, bool enteredElseLeaving);
};


#endif //BUBBAROGUEFORT_ACTIONMENU_H
