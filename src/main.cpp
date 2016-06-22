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
#include "logic/KidBandit.h"


Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

RogueFortScene* scene;


static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

void loadMeshes() {
    scene = new StartScene();
}


void idle(float timeSinceStart,float timeSinceLastCall) {
    scene->update(timeSinceLastCall * 1000,new std::vector<GameObject*>());
    if(scene->changeScene()){
        scene = new ExploreScene();
    }
}

void display(float timeSinceStart,float timeSinceLastCall) {
  renderer->drawScene(scene->getCamera(), scene->getScene(), timeSinceLastCall * 1000);
}

void resize(int newWidth, int newHeight) {
    renderer->resize(newWidth, newHeight);
    scene->resize(newWidth,newHeight);
}

int main(int argc, char *argv[]) {

    printf("%d\n",(new KidBandit())->performAttack("punch").damage);

    Logger::addLogHandler(new StdOutLogHandler());
    Logger::setLogLevel(LogLevel::INFO);
    Window* win = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubba Rogue Fort");

    win->setResizeMethod(resize);
    win->setIdleMethod(idle);
    win->setDisplayMethod(display);

    renderer = new Renderer();
    renderer->initRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    loadMeshes();

    win->start(60);
    return 0;
}

