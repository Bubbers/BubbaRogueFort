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
class InventoryItem;

class ActionMenu : public HudRenderer {
public:

    struct Action{

        std::string attack;
        std::string item;

        bool isAttack();
        bool isItem();

        Action(Bandit *performer, Bandit *target, std::string attack);
        Action(std::string item, Bandit* target);
    };


    ActionMenu(std::vector<Bandit*>* fightersInPlay,std::vector<Bandit*>* banditsInPlay, std::vector<InventoryItem*>* inventory);

    virtual void update(float dt) override;

    /**
     * If an action has been performed, the pair will
     * contain the name of the attack performed and the bandit.
     * If no action has been performed 'nullptr' will be returned.
     */
    Action* pollAction();



private:
    void createMainButtons();
    void createInventoryButtons();
    void createFighterButtons();
    void createAttacksButtons(Bandit* fighter);
    Layout* createAttackButton(Bandit* fighter, std::string attack);
    Layout* createClickButton(std::string name);
    void createTargetButtons(std::vector<Bandit*>* targets, std::function<void (Bandit*)> onTargetClick, std::function<void (void)> back);

    Font* font;
    ListLayout* buttonList;
    std::vector<Bandit*>* fighters;
    std::vector<Bandit*>* bandits;
    std::vector<InventoryItem*>* inventory;

    bool toMainButtons = false;
    bool openInventory = false;
    InventoryItem* itemPicked = nullptr;
    Bandit* openAttackMenu = nullptr;
    bool toFighters = false;
    std::pair<std::string,Bandit*>* attackPicked = nullptr;
    Action* performedAction = nullptr;

    static void onActionHover(int x, int y, Layout* hoveredOn, bool enteredElseLeaving);
    static void onActionClick(int x, int y, Layout* clickedOn, bool enteredElseLeaving);

};


#endif //BUBBAROGUEFORT_ACTIONMENU_H
