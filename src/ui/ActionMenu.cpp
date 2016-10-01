#include "ActionMenu.h"
#include <Dimension.h>
#include <HUDGraphic.h>
#include <PositioningLayout.h>
#include <ListLayout.h>
#include <TextLayout.h>
#include <FontManager.h>
#include <vector>
#include <iostream>

using namespace std;

ActionMenu::ActionMenu(vector<Bandit*>* fightersInPlay, vector<Bandit*>* banditsInPlay) {

    fighters = fightersInPlay;
    bandits = banditsInPlay;
    font = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",20);

    PositioningLayout* root = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPercentage(100));

    PositioningLayout* botBar = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPixels(103));

    HUDGraphic::Color borderColor = HUDGraphic::Color(string("#162955"));
    HUDGraphic::Color bgColor = HUDGraphic::Color(string("#2E4172"));
    HUDGraphic *hudG = new HUDGraphic(bgColor);
    botBar->setBackground(hudG->setBorder(3, 0, 0, 0, borderColor));

    buttonList = new ListLayout(ListLayout::HORIZONTAL, Dimension::fromPercentage(90),Dimension::fromPercentage(50));
    createFighterButtons();
    botBar->addChild(buttonList,Dimension::fromPercentage(5),Dimension::fromPercentage(25));

    root->addChild(botBar, Dimension::fromPixels(0), Dimension::fromPercentagePlusPixels(100, -103));

    setLayout(root);

}

void ActionMenu::updateFighterButtons() {
    buttonList->clearChildren();
    createFighterButtons();
    updateLayout();
}

void ActionMenu::createFighterButtons() {
    for(auto fighterIt : *fighters) {
        buttonList->addChild(createActionButton(fighterIt));
    }
}

void ActionMenu::update(float dt) {
    HudRenderer::update(dt);
    if(openAttackMenu != nullptr){
        buttonList->clearChildren();
        createAttacksButtons(openAttackMenu);
        openAttackMenu = nullptr;
        updateLayout();
    }
    if(backToFighters){
        backToFighters = false;
        buttonList->clearChildren();
        createFighterButtons();
        updateLayout();
    }
    if(attackPicked != nullptr){
        buttonList->clearChildren();
        createTargetButtons(attackPicked->first,attackPicked->second);
        attackPicked = nullptr;
        updateLayout();
    }
}

void ActionMenu::createTargetButtons(string action, Bandit *performer) {
    for(Bandit* bandit : *bandits){
        if(!bandit->isAlive())
            continue;
        Layout* butt = createClickButton(bandit->getName());
        butt->addClickListener([this, action, performer, bandit]
            (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void
        {
            if(!enteringElseLeaving) {
                performedAction = new Action(performer, bandit, action);
                backToFighters = true;
            }
        });

        buttonList->addChild(butt);
    }
}

void ActionMenu::createAttacksButtons(Bandit *fighter) {
    buttonList->clearChildren();
    for(string attks : fighter->getAttacks())
        buttonList->addChild(createAttackButton(fighter, attks));
    Layout* back = createClickButton("Back");
    back->addClickListener([this](int x, int y, Layout* clicked, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            backToFighters = true;
    });
    buttonList->addChild(back);
}

Layout* ActionMenu::createAttackButton(Bandit *fighter, std::string attack) {
    Layout* butt = createClickButton(attack);
    butt->addClickListener(clickedOnAttack(fighter, attack));
    return butt;
}

Layout::EventFunction ActionMenu::clickedOnAttack(Bandit *fighter, string attack) {
    return [this, attack, fighter] (int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void
    {
        if(!enteringElseLeaving) {
            attackPicked = new pair<string, Bandit *>(attack, fighter);
        }
    };
}

Layout* ActionMenu::createActionButton(Bandit* fighter) {
    Layout* butt = createClickButton(fighter->getName());
    butt->addClickListener(openAttacksOnClick(fighter));
    return butt;

}
Layout* ActionMenu::createClickButton(string name) {
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

Layout::EventFunction ActionMenu::openAttacksOnClick(Bandit *fighter) {
    return [this, fighter] (int x, int y, Layout *clickedOn, bool enteredElseLeaving) -> void
    {
        if(!enteredElseLeaving)
            openAttackMenu = fighter;
    };
}

ActionMenu::Action* ActionMenu::pollAction() {
    Action* temp = performedAction;
    performedAction = nullptr;
    return temp;
}

ActionMenu::Action::Action(Bandit *performer, Bandit *target, string attack)
        : performer(performer), target(target), attack(attack) { };
