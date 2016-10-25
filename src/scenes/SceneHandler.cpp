//
// Created by johan on 2016-06-22.
//

#include "SceneHandler.h"
#include "StartScene.h"
#include "ExploreScene.h"
#include "constants.h"
#include "BattleScene.h"

SceneHandler::SceneHandler(Player* player, Camera* camera) {
    startScene = new StartScene();
    explorerScene = new ExploreScene(camera);

    scene = startScene;
    this->player = player;
    this->camera = camera;
}

void SceneHandler::idle(float timeSinceStart,float timeSinceLastCall) {
    auto emptyVector = std::vector<std::shared_ptr<GameObject>>();
    scene->update(timeSinceLastCall * 1000, emptyVector);
    if(scene->changeScene()){

        scene->sceneExit(player, camera);

        std::string newSceneName = scene->getNewSceneName();
        if(newSceneName == EXPLORE_SCENE) {
            scene = explorerScene;
        } else if (newSceneName == START_SCENE) {
            scene = startScene;
        } else if(newSceneName == BATTLE_SCENE) {
            scene = new BattleScene();
        }

        scene->sceneEntry(player, camera);

        scene->setShouldChangeScene(false);
    }
}

RogueFortScene* SceneHandler::getCurrentScene() {
    return scene;
}

void SceneHandler::resize(int newWidth, int newHeight) {
    startScene->resize(newWidth,newHeight);
    explorerScene->resize(newWidth,newHeight);
}
