//
// Created by simon on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_ACTIONMENU_H
#define BUBBAROGUEFORT_ACTIONMENU_H


#include <HudRenderer.h>
#include <Layout.h>
#include <ListLayout.h>
#include "../logic/Bandit.h"

class Font;

class ActionMenu : public HudRenderer {
public:
    ActionMenu(std::vector<Bandit*>* banditsInPlay);
    virtual void update(float dt) override;

private:
    void createBanditButtons(std::vector<Bandit*>* banditsInPlay);
    Layout* createActionButton(Bandit* bandit);
    void createAttacksButtons(Bandit* bandit);
    Layout* createAttackButton(Bandit* bandit, std::string attack);

    Font* font;
    ListLayout* buttonList;

    Bandit* openAttackMenu = nullptr;
    bool backToBandits = false;

    static void onActionHover(int x, int y, Layout* hoveredOn, bool enteredElseLeaving);
    static void onActionClick(int x, int y, Layout* clickedOn, bool enteredElseLeaving);
    Layout::EventFunction openAttacksOnClick(Bandit* bandit);
};


#endif //BUBBAROGUEFORT_ACTIONMENU_H
