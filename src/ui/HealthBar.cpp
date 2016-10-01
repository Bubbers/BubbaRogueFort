//
// Created by simon on 2016-10-01.
//

#include <PositioningLayout.h>
#include <HUDGraphic.h>
#include <ListLayout.h>
#include <TextLayout.h>
#include <FontManager.h>
#include "HealthBar.h"
#include "../logic/Bandit.h"
#include "GLSquare.h"

HealthBar::HealthBar(Bandit* bandit) : bandit(bandit), PositioningLayout(Dimension::fromPercentage(50),Dimension::fromPercentage(50)){

    ListLayout* root = new ListLayout(ListLayout::VERTICAL,Dimension::fromPixels(100),Dimension::fromPixels(35));

    Font* font = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",20);
    TextLayout* name = new TextLayout(bandit->getName(),font,Dimension::fill(),Dimension::fromPixels(25));

    PositioningLayout* border = new PositioningLayout(Dimension::fill(),Dimension::fromPixels(10));
    border->setBackground((new HUDGraphic(HUDGraphic::Color(string("#000"),0)))->setBorder(1, HUDGraphic::Color(string("#000"))));

    bar = new PositioningLayout(Dimension::fromPercentagePlusPixels(100,-2),Dimension::fromPercentagePlusPixels(100,-2));
    bar->setBackground((new HUDGraphic(HUDGraphic::Color(string("#f00"))))->setCenterOffset(Dimension::fromPercentage(50),Dimension::fromPixels(0)));
    border->addChild(bar,Dimension::fromPixels(1),Dimension::fromPixels(1));

    root->addChild(name);
    root->addChild(border);

    addChild(root,Dimension::fromPercentage(-15),Dimension::fromPercentage(-35));



    bandit->addDamageListener([this](int health) -> void { this->damageTaken(); });

}

void HealthBar::damageTaken() {

    if(bar->getRenderedBackground() != nullptr) {
        bar->getRenderedBackground()->setScale(make_vector((float)bandit->getHealth()/(float)bandit->getMaxHealth(),1.0f));
    }
    if(bandit->getHealth() == 0)
        dead = true;

}

void HealthBar::getGLSquares(float layoutXPos, float layoutYPos, float layoutWidth, float layoutHeight,
                             map<string, IHudDrawable *> *list) {
    if(!dead) {
        PositioningLayout::getGLSquares(layoutXPos, layoutYPos, layoutWidth, layoutHeight, list);
        damageTaken();
    }
}
