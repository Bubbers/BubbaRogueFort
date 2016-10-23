/*
 * This file is a part of BubbaRogueFort
 * Copyright (C) 2016 Bubbers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <StandardRenderer.h>
#include <Scene.h>
#include <StdOutLogHandler.h>
#include "components/PlayerCamera.h"
#include <KeyboardButton.h>
#include <Globals.h>
#include <constants.h>
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "scenes/StartScene.h"
#include "scenes/ExploreScene.h"
#include "level/LevelFileReader.h"
#include "logic/KidBandit.h"
#include "scenes/SceneHandler.h"
#include "logic/Player.h"
#include "Logger.h"

using namespace chag;

Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

SceneHandler *sceneHandler;
PlayerCamera *camera;

void idle(float timeSinceStart,float timeSinceLastCall) {
    sceneHandler->idle(timeSinceStart, timeSinceLastCall);
}

void display(float timeSinceStart,float timeSinceLastCall) {
  renderer->drawScene(sceneHandler->getCurrentScene()->getCamera(), sceneHandler->getCurrentScene()->getScene(), timeSinceLastCall * 1000);
}

void resize(int newWidth, int newHeight) {
    renderer->resize(newWidth, newHeight);
    sceneHandler->resize(newWidth, newHeight);
}

void createCamera() {
    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);


}

int main(int argc, char *argv[]) {

    //srand(); TODO

    Logger::addLogHandler(new StdOutLogHandler());
    Logger::setLogLevel(LogLevel::WARNING);
    Window* win = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubba Rogue Fort");

    win->setResizeMethod(resize);
    win->setIdleMethod(idle);
    win->setDisplayMethod(display);

    renderer = new Renderer();
    renderer->initRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    createCamera();
    sceneHandler = new SceneHandler(new Player(),camera);

    win->start(60);
    return 0;
}

