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
MoveComponent *moveComponent;
enum Functions: int {MOVE_H,MOVE_V};

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
                 make_vector(10.0f, 10.0f, 10.0f),
                 make_vector(0.0f, 0.0f, 0.0f),
                 UP_VECTOR, 45, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT),
                 0.1f, 50000.0f);

    /* Add the player to the scene */

  for(int i=1;i<5;i++){
    player = new GameObject(playerMesh);
    player->setLocation(make_vector(0.50f, 0.50f,0.50f-i*5.0f));
    StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
    player->addRenderComponent(stdrenderer);
    player->setDynamic(true);

    /* Add the player to the scene */
    scene.addShadowCaster(player);
  }



  // character to move
  player = new GameObject(playerMesh);
  moveComponent = new MoveComponent(player);
  player->addComponent(moveComponent);



  player->setLocation(make_vector(0.50f, 0.50f,0.50f));
  StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
  player->addRenderComponent(stdrenderer);
  player->setDynamic(true);

  /* Add the player to the scene */
  scene.addShadowCaster(player);

  player->addComponent(camera);





    /* Load player mesh and attach it to the player GameObject */
  Mesh *FloorMesh = ResourceManager::loadAndFetchMesh("../meshes/ground.obj");
  // references are from the the build folder


    GameObject* floor = new GameObject(FloorMesh);
    floor->setLocation(make_vector(0.0f, 0.0f,0.0f));
    StandardRenderer *floorrenderer = new StandardRenderer(FloorMesh, floor, standardShader);
    floor->addRenderComponent(floorrenderer);
    floor->setDynamic(true);

    /* Add the player to the scene */
    scene.addShadowCaster(floor);

}
void initKeyBindings(){
  ControlsManager* cm = ControlsManager::getInstance();
  cm->addBinding(MOVE_H,{new KeyboardButton(sf::Keyboard::D,sf::Keyboard::A)});
  cm->addBinding(MOVE_V,{new KeyboardButton(sf::Keyboard::W,sf::Keyboard::S)});

}


void checkKeyboardKeys(){
  ControlsManager*  cm = ControlsManager::getInstance();
  ControlStatus   cs_H = cm->getStatus(MOVE_H);
  ControlStatus   cs_V = cm->getStatus(MOVE_V);

  if(cs_H.isActive() && cs_V.isActive())
  {
    if(cs_H.getValue()>0 && cs_V.getValue()<0)
    {
      moveComponent->setVelocity(make_vector(0.01f,0.0f,0.01f)/sqrtf(2));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/4));
    }
    else if(cs_H.getValue()>0 && cs_V.getValue()>0)
    {
      moveComponent->setVelocity(make_vector(0.01f,0.0f,-0.01f)/sqrtf(2));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/-4));
    }
    else if(cs_H.getValue()<0 && cs_V.getValue()<0)
    {
      moveComponent->setVelocity(make_vector(-0.01f,0.0f,0.01f)/sqrtf(2));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/-4));
    }
    else{
      moveComponent->setVelocity(make_vector(-0.01f,0.0f,-0.01f)/sqrtf(2));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/4));
    }
  }
  else if(cs_H.isActive())
  {
    if(cs_H.getValue()>0)
    {
      moveComponent->setVelocity(make_vector(0.01f,0.0f,0.0f));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/2));
    }
    else{
      moveComponent->setVelocity(make_vector(-0.01f,0.0f,0.0f));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/-2));
    }
  }
  else if(cs_V.isActive())
  {
    if(cs_V.getValue()<0) {
      moveComponent->setVelocity(make_vector(0.0f,0.0f,0.01f));
      //moveComponent->setRotation(make_quaternion(make_rotation_y<float4x4>(0.005f)));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI));
      //Quaternion rotation = player->getAbsoluteRotation();

    }
    else{
      moveComponent->setVelocity(make_vector(0.0f,-0.0f,-0.01f));
      player->setRotation(make_quaternion_axis_angle(UP_VECTOR,M_PI/-1.0f));
      //moveComponent->setRotationSpeed(make_quaternion(make_rotation_y<float4x4>(-0.005f)));
    }
  }
  else if(!cs_H.isActive() && !cs_V.isActive()){
    moveComponent->setVelocity(make_vector(0.0f,0.0f,0.0f));
    //moveComponent->setRotationSpeed(make_quaternion(make_rotation_y<float4x4>(0.00000f)));
  }
}


void idle(float timeSinceStart,float timeSinceLastCall) {

    camera->setLookAt(player->getAbsoluteLocation());
  scene.update(timeSinceLastCall*1000,new std::vector<GameObject*>());
  checkKeyboardKeys();
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
    initKeyBindings();


  win->start(60);
  return 0;
}

