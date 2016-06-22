#include <StandardRenderer.h>
#include <Scene.h>
#include <StdOutLogHandler.h>
#include "components/PlayerCamera.h"
#include <KeyboardButton.h>
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "scenes/StartScene.h"
#include "scenes/ExploreScene.h"
#include "level/LevelFileReader.h"
#include "scenes/SceneHandler.h"


Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

SceneHandler *sceneHandler;

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

int main(int argc, char *argv[]) {
    Logger::addLogHandler(new StdOutLogHandler());
    Logger::setLogLevel(LogLevel::INFO);
    Window* win = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubba Rogue Fort");

    win->setResizeMethod(resize);
    win->setIdleMethod(idle);
    win->setDisplayMethod(display);

    renderer = new Renderer();
    renderer->initRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    sceneHandler = new SceneHandler;

    win->start(60);
    return 0;
}

