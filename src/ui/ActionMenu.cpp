//
// Created by simon on 2016-06-21.
//

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

ActionMenu::ActionMenu(vector<Bandit*>* banditsInPlay) {

    bandits = banditsInPlay;
    font = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",20);

    PositioningLayout* root = new PositioningLayout(Dimension::fromPercentage(100),Dimension::fromPercentage(100));

    PositioningLayout* botBar = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPixels(103));
    botBar->setBackground((new HUDGraphic(HUDGraphic::Color(string("#2E4172"))))->setBorder(3, 0, 0, 0, HUDGraphic::Color(string("#162955"))));

    buttonList = new ListLayout(ListLayout::HORIZONTAL, Dimension::fromPercentage(90),Dimension::fromPercentage(50));
    createBanditButtons();
    botBar->addChild(buttonList,Dimension::fromPercentage(5),Dimension::fromPercentage(25));

    root->addChild(botBar, Dimension::fromPixels(0), Dimension::fromPercentagePlusPixels(100, -103));

    setLayout(root);

}

void ActionMenu::createBanditButtons() {
    for(auto banditIt : *bandits){
        buttonList->addChild(createActionButton(banditIt));
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
    if(backToBandits){
        backToBandits = false;
        buttonList->clearChildren();
        createBanditButtons();
        updateLayout();
    }
}

void ActionMenu::createAttacksButtons(Bandit *bandit) {
    buttonList->clearChildren();
    for(string attks : bandit->getAttacks())
        buttonList->addChild(createAttackButton(bandit,attks));
    Layout* back = createClickButton("Back");
    back->addClickListener([=](int x, int y, Layout* clicked, bool enteringElseLeaving) -> void {
        if(!enteringElseLeaving)
            backToBandits = true;
    });
    buttonList->addChild(back);
}

Layout* ActionMenu::createAttackButton(Bandit *bandit, std::string attack) {
    Layout* butt = createClickButton(attack);
    butt->addClickListener(clickedOnAttack(bandit,attack));
    return butt;
}

Layout::EventFunction ActionMenu::clickedOnAttack(Bandit *bandit, string attack) {
    return [=](int x, int y, Layout* clickedOn, bool enteringElseLeaving) -> void{
        if(!enteringElseLeaving) {
            actionPerformed = new pair<string, Bandit *>(attack, bandit);
            backToBandits = true;
        }
    };
}

Layout* ActionMenu::createActionButton(Bandit* bandit) {
    Layout* butt = createClickButton(bandit->getName());
    butt->addClickListener(openAttacksOnClick(bandit));
    return butt;

}
Layout* ActionMenu::createClickButton(string name) {
    TextLayout* butt = new TextLayout(name,font,Dimension::fill(),Dimension::fill());
    butt->setPadding(12);
    butt->setBackground(new HUDGraphic(HUDGraphic::Color("#4F628E")));
    butt->getGraphic()->setBorder(2,HUDGraphic::Color("#162955"));
    butt->addHoverListener(onActionHover)->addClickListener(onActionClick);
    return butt;
}

void ActionMenu::onActionHover(int x, int y, Layout *hoveredOn, bool enteredElseLeaving) {
    int size = enteredElseLeaving ? 4 : 2;
    hoveredOn->getGraphic()->setBorderSize(size,size,size,size);
    if(!enteredElseLeaving)
        hoveredOn->getGraphic()->setBackground(HUDGraphic::Color("#4F628E"));
    hoveredOn->updateGraphic();
}

void ActionMenu::onActionClick(int x, int y, Layout *clickedOn, bool enteredElseLeaving) {
    HUDGraphic::Color color = HUDGraphic::Color(enteredElseLeaving ? "#7887AB" : "#4F628E");
    clickedOn->getGraphic()->setBackground(color);
}

Layout::EventFunction ActionMenu::openAttacksOnClick(Bandit *bandit) {
    return [=,bandit](int x, int y, Layout *clickedOn, bool enteredElseLeaving) -> void {
        if(!enteredElseLeaving)
            openAttackMenu = bandit;
    };
}

std::pair<string,Bandit*>* ActionMenu::pollAction() {
    pair<string,Bandit*>* temp = actionPerformed;
    actionPerformed = nullptr;
    return temp;
}