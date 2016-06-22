//
// Created by johan on 2016-06-22.
//

#include "SceneHandler.h"
#include "StartScene.h"
#include "ExploreScene.h"

SceneHandler::SceneHandler() {
    startScene = new StartScene();
    explorerScene = new ExploreScene();

    scene = startScene;
}

void SceneHandler::idle(float timeSinceStart,float timeSinceLastCall) {
    scene->update(timeSinceLastCall * 1000,new std::vector<GameObject*>());
    if(scene->changeScene()){

        scene->sceneExit();

        std::string newSceneName = scene->getNewSceneName();
        if(newSceneName == "ExploreScene") {
            scene = explorerScene;
        } else if (newSceneName == "StartScene") {
            scene = startScene;
        }

        scene->sceneEntry();

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