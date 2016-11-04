#include "ActionMenu.h"
#include "../logic/InventoryItem.h"
#include <Dimension.h>
#include <HUDGraphic.h>
#include <PositioningLayout.h>
#include <ListLayout.h>
#include <TextLayout.h>
#include <FontManager.h>
#include <vector>
#include <iostream>
#include "../logic/Bandit.h"

ActionMenu::ActionMenu(std::vector<Bandit*>* fightersInPlay, std::vector<Bandit*>* banditsInPlay, std::vector<InventoryItem*>* inventory) {

    fighters = fightersInPlay;
    bandits = banditsInPlay;
    this->inventory = inventory;
    font = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",20);

    PositioningLayout* root = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPercentage(100));

    PositioningLayout* botBar = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPixels(103));

    HUDGraphic::Color borderColor = HUDGraphic::Color(std::string("#162955"));
    HUDGraphic::Color bgColor = HUDGraphic::Color(std::string("#2E4172"));
    HUDGraphic *hudG = new HUDGraphic(bgColor);
    botBar->setBackground(hudG->setBorder(3, 0, 0, 0, borderColor));

    buttonList = new ListLayout(ListLayout::HORIZONTAL, Dimension::fromPercentage(90),Dimension::fromPercentage(50));
    createMainButtons();
    botBar->addChild(buttonList,Dimension::fromPercentage(5),Dimension::fromPercentage(25));

    root->addChild(botBar, Dimension::fromPixels(0), Dimension::fromPercentagePlusPixels(100, -103));

    setLayout(root);

}

void ActionMenu::createMainButtons() {
    buttonList->clearChildren();
    Layout* fightButton = createClickButton("Fight");
    fightButton->addClickListener([this] (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            toFighters = true;
    });
    buttonList->addChild(fightButton);
    Layout* inventoryButton = createClickButton("Inventory");
    inventoryButton->addClickListener([this] (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            openInventory = true;
    });
    buttonList->addChild(inventoryButton);
}

void ActionMenu::createInventoryButtons() {

    for(auto item : *inventory) {
        buttonList->clearChildren();
        Layout *butt = createClickButton(item->getName());
        butt->addClickListener([this, item] (int x, int y, Layout *clickedOn, bool enteringElseLeaving) -> void {
            if (!enteringElseLeaving) {
                itemPicked = item;
            }
        });

        buttonList->addChild(butt);
    }
    buttonList->addChild(createClickButton("Back")->addClickListener([this](int x, int y, Layout *clickedOn, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            toMainButtons = true;
    }));

}

void ActionMenu::createFighterButtons() {
    createTargetButtons(fighters,[this] (Bandit* target) -> void {
        openAttackMenu = target;
    },[this] () -> void {
        toMainButtons = true;
    });
}

void ActionMenu::createAttacksButtons(Bandit *fighter) {

    buttonList->clearChildren();
    for(std::string attks : fighter->getAttacks())
        buttonList->addChild(createAttackButton(fighter, attks));
    Layout* back = createClickButton("Back");
    back->addClickListener([this](int x, int y, Layout* clicked, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            toFighters = true;
    });
    buttonList->addChild(back);

}

Layout* ActionMenu::createAttackButton(Bandit *fighter, std::string attack) {
    Layout* butt = createClickButton(attack);
    butt->addClickListener([this, attack, fighter] (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving) {
            attackPicked = new std::pair<std::string, Bandit *>(attack, fighter);
        }
    });
    return butt;
}

void ActionMenu::update(float dt) {
    HudRenderer::update(dt);
    if(toMainButtons){
        buttonList->clearChildren();
        createMainButtons();
        toMainButtons = false;
        updateLayout();
    }
    if(openInventory){
        buttonList->clearChildren();
        createInventoryButtons();
        openInventory = false;
        updateLayout();
    }
    if(itemPicked != nullptr){
        buttonList->clearChildren();
        InventoryItem* item = itemPicked;
        createTargetButtons(itemPicked->getTarget() == InventoryItem::HOSTILE ? bandits : fighters, [this,item](Bandit* target) -> void {
            item->affect(target);
            toMainButtons = true;
        },[this,item]() -> void {
            openInventory = true;
        });
        itemPicked = nullptr;
        updateLayout();
    }
    if(openAttackMenu != nullptr){
        buttonList->clearChildren();
        createAttacksButtons(openAttackMenu);
        openAttackMenu = nullptr;
        updateLayout();
    }
    if(toFighters){
        toFighters = false;
        buttonList->clearChildren();
        createFighterButtons();
        updateLayout();
    }
    if(attackPicked != nullptr){
        buttonList->clearChildren();
        std::pair<std::string,Bandit*> attack = *attackPicked;
        createTargetButtons(bandits,[this,attack](Bandit* target) -> void {
            performedAction = new Action(attack.second,target,attack.first);
            toMainButtons = true;
        },[this,attack] () -> void {
            openAttackMenu = attack.second;
        });

        attackPicked = nullptr;
        updateLayout();
    }
}

void ActionMenu::createTargetButtons(std::vector<Bandit*>* targets, std::function<void (Bandit*)> onTargetClick, std::function<void (void)> back) {
    for(Bandit* bandit : *targets){
        if(!bandit->isAlive())
            continue;
        Layout* butt = createClickButton(bandit->getName());
        butt->addClickListener([this, bandit, onTargetClick]
            (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void
        {
            if(!enteringElseLeaving) {
                onTargetClick(bandit);
            }
        });

        buttonList->addChild(butt);
    }
    Layout* backButton = createClickButton("Back");
    backButton->addClickListener([back] (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            back();
    });
    buttonList->addChild(backButton);
}

Layout* ActionMenu::createClickButton(std::string name) {
    TextLayout* butt = new TextLayout(name, font, Dimension::fill(), Dimension::fill());
    butt->setPadding(12);
    butt->setBackground(new HUDGraphic(HUDGraphic::Color("#4F628E")));
    butt->getGraphic()->setBorder(2, HUDGraphic::Color("#162955"));
    butt->addHoverListener(onActionHover)->addClickListener(onActionClick);
    return butt;
}

void ActionMenu::onActionHover(int x, int y, Layout *hoveredOn, bool enteredElseLeaving) {
    int size = enteredElseLeaving ? 4 : 2;
    hoveredOn->getGraphic()->setBorderSize(size, size, size, size);
    if(!enteredElseLeaving)
        hoveredOn->getGraphic()->setBackground(HUDGraphic::Color("#4F628E"));
    hoveredOn->updateGraphic();
}

void ActionMenu::onActionClick(int x, int y, Layout *clickedOn, bool enteredElseLeaving) {
    HUDGraphic::Color color = HUDGraphic::Color(enteredElseLeaving ? "#7887AB" : "#4F628E");
    clickedOn->getGraphic()->setBackground(color);
}

ActionMenu::Action* ActionMenu::pollAction() {
    Action* temp = performedAction;
    performedAction = nullptr;
    return temp;
}

ActionMenu::Action::Action(Bandit *performer, Bandit *target, std::string attack)
        : performer(performer), target(target), attack(attack) { }

ActionMenu::Action::Action(std::string item, Bandit *target)
    : item(item), target(target) { };

bool ActionMenu::Action::isAttack() {
    return !attack.empty();
}

bool ActionMenu::Action::isItem() {
    return !item.empty();
}

