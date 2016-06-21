//
// Created by simon on 2016-06-21.
//

#include <TextLayout.h>
#include <PositioningLayout.h>
#include <FontManager.h>
#include <HUDGraphic.h>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "StartScene.h"
#include "HudRenderer.h"
#include "../IdentityCamera.h"

using namespace std::placeholders;

StartScene::StartScene() {
    GameObject* hud = new GameObject();
    hudRenderer = new HudRenderer();

    titleFont = FontManager::getInstance()->loadAndFetchFont("../fonts/Ubuntu-M.ttf",40);
    playFont = titleFont;

    hudRenderer->setLayout(createMenu());
    hud->addRenderComponent(hudRenderer);
    addTransparentObject(hud);
}

Layout* StartScene::createMenu() {

    PositioningLayout* root = new PositioningLayout(Dimension::fromPercentage(100),Dimension::fromPercentage(100));
    root->setBackground(new HUDGraphic(HUDGraphic::Color("#555")));
    TextLayout* title = new TextLayout(std::string("Bubba Rogue Fort"), titleFont, Dimension::fromPixels(400),Dimension::fromPixels(40));

    root->addChild(title,Dimension::fromPercentagePlusPixels(50,-200),Dimension::fromPercentage(20));

    TextLayout* playButton = new TextLayout(std::string("Play"),playFont,Dimension::fromPixels(200),Dimension::fromPixels(60));
    playButton->setBackground(new HUDGraphic(HUDGraphic::Color(string("#555"))));
    playButton->addHoverListener(hoverPlay);
    playButton->addClickListener([=](int x, int y, Layout* l,bool e) -> void {this->clickPlay(x,y,l,e);});
    root->addChild(playButton,Dimension::fromPercentagePlusPixels(50,-100),Dimension::fromPercentagePlusPixels(50,-30));
    return root;

}

void StartScene::hoverPlay(int x, int y, Layout* hoveringOn, bool enteringElseLeaving) {
    hoveringOn->getGraphic()->setBackground(HUDGraphic::Color(enteringElseLeaving ? "#aaa" : "#555"));
    hoveringOn->updateGraphic();
}

void StartScene::clickPlay(int x, int y, Layout *clickedOn, bool enteringElseLeaving) {
    clickedOn->getGraphic()->setBackground(HUDGraphic::Color(enteringElseLeaving ? "#333" : "#aaa"));
    clickedOn->updateGraphic();
    if(!enteringElseLeaving)
        playIsClicked = true;
}

Camera* StartScene::getCamera() {
    return camera;
}

bool StartScene::changeScene() {
    return playIsClicked;
}

void StartScene::resize(int x, int y) {
    hudRenderer->updateLayout();
}