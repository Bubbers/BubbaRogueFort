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

    /**
     * If an action has been performed, the pair will
     * contain the name of the attack performed and the bandit.
     * If no action has benn performed 'nullptr' will be returned.
     */
    std::pair<string,Bandit*>* pollAction();

private:
    void createBanditButtons();
    Layout* createActionButton(Bandit* bandit);
    void createAttacksButtons(Bandit* bandit);
    Layout* createAttackButton(Bandit* bandit, std::string attack);
    Layout* createClickButton(string name);

    Font* font;
    ListLayout* buttonList;
    std::vector<Bandit*>* bandits;

    Bandit* openAttackMenu = nullptr;
    bool backToBandits = false;
    std::pair<string,Bandit*>* actionPerformed = nullptr;

    static void onActionHover(int x, int y, Layout* hoveredOn, bool enteredElseLeaving);
    static void onActionClick(int x, int y, Layout* clickedOn, bool enteredElseLeaving);
    Layout::EventFunction openAttacksOnClick(Bandit* bandit);
    Layout::EventFunction clickedOnAttack(Bandit* bandit, string attack);
};


#endif //BUBBAROGUEFORT_ACTIONMENU_H
