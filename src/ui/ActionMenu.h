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

    struct Action{
        Bandit* performer;
        Bandit* target;
        std::string attack;

        Action(Bandit *performer, Bandit *target, std::string attack);
    };

    ActionMenu(std::vector<Bandit*>* fightersInPlay, std::vector<Bandit*>* banditsInPlay);
    virtual void update(float dt) override;

    /**
     * If an action has been performed, the pair will
     * contain the name of the attack performed and the bandit.
     * If no action has been performed 'nullptr' will be returned.
     */
    Action* pollAction();


    void updateFighterButtons();

private:
    void createFighterButtons();
    Layout* createActionButton(Bandit* fighter);
    void createAttacksButtons(Bandit* fighter);
    Layout* createAttackButton(Bandit* fighter, std::string attack);
    Layout* createClickButton(std::string name);
    void createTargetButtons(std::string action, Bandit* performer);

    Font* font;
    ListLayout* buttonList;
    std::vector<Bandit*>* fighters;
    std::vector<Bandit*>* bandits;

    Bandit* openAttackMenu = nullptr;
    bool backToFighters = false;
    std::pair<std::string, Bandit*>* attackPicked = nullptr;
    Action* performedAction = nullptr;

    static void onActionHover(int x, int y, Layout* hoveredOn, bool enteredElseLeaving);
    static void onActionClick(int x, int y, Layout* clickedOn, bool enteredElseLeaving);
    Layout::EventFunction openAttacksOnClick(Bandit* fighter);
    Layout::EventFunction clickedOnAttack(Bandit* fighter, std::string attack);
};


#endif //BUBBAROGUEFORT_ACTIONMENU_H
