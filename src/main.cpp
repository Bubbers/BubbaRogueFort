#include <GL/glew.h>
#include <GL/freeglut.h>
#include <PerspectiveCamera.h>
#include <StandardRenderer.h>
#include <Scene.h>
#include <GameObject.h>
#include "ShaderProgram.h"
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "constants.h"

Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Camera *camera;
static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

void setupCamera() {
  camera = new PerspectiveCamera(
               make_vector(10.0f, 10.0f, 10.0f),
               make_vector(0.0f, 0.0f, 0.0f),
               UP_VECTOR, 45, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT),
               0.1f, 50000.0f);
}

GameObject *player;
Scene scene;

void loadMeshes() {
  /* Shader setup done once for all meshes that use it */
  ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

  /* Load player mesh and attach it to the player GameObject */
  Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/player.fbx");
                                            // references are from the the build folder

  player = new GameObject(playerMesh);
  player->setLocation(make_vector(0.0f, 0.0f, 0.0f));
  StandardRenderer* stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
  player->addRenderComponent(stdrenderer);
  player->setDynamic(true);

  /* Add the player to the scene */
  scene.addShadowCaster(player);
}

void idle(float timeSinceStart,float timeSinceLastCall) {
}

void display(float timeSinceStart,float timeSinceLastCall) {
  renderer->drawScene(camera, &scene, timeSinceStart);
}

void resize(int newWidth, int newHeight) {
  renderer->resize(newWidth, newHeight);
}

int main(int argc, char *argv[]) {
  Window* win = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bubba Rogue Fort");

  win->setResizeMethod(resize);
  win->setIdleMethod(idle);
  win->setDisplayMethod(display);

  renderer = new Renderer();
  renderer->initRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);

  loadMeshes();
  setupCamera();

  win->start(60);
  return 0;
}

