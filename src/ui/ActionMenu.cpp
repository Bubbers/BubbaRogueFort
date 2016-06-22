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

    font = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",20);

    PositioningLayout* root = new PositioningLayout(Dimension::fromPercentage(100),Dimension::fromPercentage(100));

    PositioningLayout* botBar = new PositioningLayout(Dimension::fromPercentage(100), Dimension::fromPixels(103));
    botBar->setBackground((new HUDGraphic(HUDGraphic::Color(string("#2E4172"))))->setBorder(3, 0, 0, 0, HUDGraphic::Color(string("#162955"))));

    buttonList = new ListLayout(ListLayout::HORIZONTAL, Dimension::fromPercentage(90),Dimension::fromPercentage(50));
    createBanditButtons(banditsInPlay);
    botBar->addChild(buttonList,Dimension::fromPercentage(5),Dimension::fromPercentage(25));

    root->addChild(botBar, Dimension::fromPixels(0), Dimension::fromPercentagePlusPixels(100, -103));

    setLayout(root);

}

void ActionMenu::createBanditButtons(std::vector<Bandit *> *banditsInPlay) {
    for(auto banditIt : *banditsInPlay){
        buttonList->addChild(createActionButton(banditIt));
    }
}

void ActionMenu::update(float dt) {
    if(openAttackMenu != nullptr){
        buttonList->clearChildren();
        createActionButton(nullptr);
    }
}

Layout* ActionMenu::createActionButton(Bandit* bandit) {
    TextLayout* butt = new TextLayout(bandit->getName(),font,Dimension::fill(),Dimension::fill());
    butt->setPadding(12);
    butt->setBackground(new HUDGraphic(HUDGraphic::Color("#4F628E")));
    butt->getGraphic()->setBorder(2,HUDGraphic::Color("#162955"));
    butt->addHoverListener(onActionHover)->addClickListener(onActionClick)->addClickListener(openAttacksOnClick(bandit));
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
        //openAttackMenu = bandit;
    };
}