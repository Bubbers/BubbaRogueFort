#include <GL/glew.h>
#include <GL/freeglut.h>
#include <StandardRenderer.h>
#include <Scene.h>
#include <GameObject.h>
#include "components/PlayerCamera.h"
#include <MoveComponent.h>
#include <ControlsManager.h>
#include <KeyboardButton.h>
#include "ShaderProgram.h"
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "constants.h"
#include <vector>
#include <ColliderFactory.h>
#include <components/MoveComponentWithCollision.h>
#include "level/LevelFileReader.h"
#include "StdOutLogHandler.h"

Renderer *renderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Camera *camera;
static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

// Globals
GameObject *player;
Scene scene;
MoveComponentWithCollision *moveComponent;
Collider *collider;


void createLight(){

    DirectionalLight directionalLight;
    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.50f,0.50f,0.50f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);
    scene.directionalLight=directionalLight;

}

void loadMeshes() {

    scene = *(LevelFileReader::read("../levels/test.level"));

    /* Shader setup done once for all meshes that use it */
    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/player.fbx");
    // references are from the the build folder


    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            UP_VECTOR, 45, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT),
            0.1f, 50000.0f);

    // character to move
    player = new GameObject(playerMesh);
    moveComponent = new MoveComponentWithCollision(player);
    player->addComponent(moveComponent);



    player->setLocation(make_vector(0.50f, 0.50f,0.50f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);

    /* Add the player to the scene */
    scene.addShadowCaster(player);

    player->addComponent(camera);
    player->setIdentifier(0);
    player->addCollidesWith(1);
}






void idle(float timeSinceStart,float timeSinceLastCall) {
    camera->setLookAt(player->getAbsoluteLocation());
    scene.update(timeSinceLastCall*1000,new std::vector<GameObject*>());
    collider->updateCollision(&scene);
}

void display(float timeSinceStart,float timeSinceLastCall) {
    renderer->drawScene(camera, &scene, timeSinceStart);
}

void resize(int newWidth, int newHeight) {
    renderer->resize(newWidth, newHeight);
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

    loadMeshes();
    createLight();
    collider = ColliderFactory::getTwoPhaseCollider();


    win->start(60);
    return 0;
}

