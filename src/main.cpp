#include <GL/glew.h>
#include <GL/freeglut.h>
#include <StandardRenderer.h>
#include <Scene.h>
#include <GameObject.h>
#include <StdOutLogHandler.h>
#include "components/PlayerCamera.h"
#include <MoveComponent.h>
#include <ControlsManager.h>
#include <KeyboardButton.h>
#include "ShaderProgram.h"
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "constants.h"
#include "scenes/StartScene.h"
#include "IdentityCamera.h"
#include "scenes/ExploreScene.h"
#include <vector>
#include "level/LevelFileReader.h"
#include "StdOutLogHandler.h"
#include "controls.h"

Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Camera *camera;
static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

RogueFortScene* scene;


void loadMeshes() {

    scene = new StartScene();

}

void idle(float timeSinceStart,float timeSinceLastCall) {
  scene->update(timeSinceStart*1000.0f,new std::vector<GameObject*>());
  if(scene->changeScene()){
    scene = new ExploreScene();
  }
}

void display(float timeSinceStart,float timeSinceLastCall) {
  renderer->drawScene(scene->getCamera(), scene, timeSinceStart);
}

void resize(int newWidth, int newHeight) {
  renderer->resize(newWidth, newHeight);
  scene->resize(newWidth,newHeight);
}

int main(int argc, char *argv[]) {
  Logger::addLogHandler(new StdOutLogHandler());
  Logger::setLogLevel(LogLevel::SEVERE);
  Window* win = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubba Rogue Fort");

    win->setResizeMethod(resize);
    win->setIdleMethod(idle);
    win->setDisplayMethod(display);

    renderer = new Renderer();
    renderer->initRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
  scene = new StartScene();

  win->start(60);
  return 0;
}

