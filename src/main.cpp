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


Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

SceneHandler *sceneHandler;
PlayerCamera *camera;
GameObject *player;

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

void createPlayer() {
    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);

    /* Shader setup done once for all meshes that use it */
    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/bubba.obj");
    // references are from the the build folder

    // character to move
    player = new GameObject(playerMesh);
    MoveComponentWithCollision *moveComponent = new MoveComponentWithCollision(player);
    player->addComponent(moveComponent);

    player->setLocation(make_vector(0.0f, 0.2f,0.0f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);
    player->setIdentifier(0);
    player->addCollidesWith(1);

    player->addComponent(camera);

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

    createPlayer();
    sceneHandler = new SceneHandler(player, camera);


    win->start(60);
    return 0;
}

