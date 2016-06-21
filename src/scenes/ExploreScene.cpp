//
// Created by simon on 2016-06-21.
//

#include <PerspectiveCamera.h>
#include <ResourceManager.h>
#include <constants.h>
#include <StandardRenderer.h>
#include <Globals.h>
#include <ControlsManager.h>
#include <KeyboardButton.h>
#include "ExploreScene.h"
#include "../components/PlayerCamera.h"
#include <controls.h>
#include <ActionMenu.h>

float3 UP_VECTOR = make_vector(0.0f,1.0f,0.0f);

ExploreScene::ExploreScene() {

    initKeyBindings();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(10.0f, 10.0f, 10.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);

    /* Shader setup done once for all meshes that use it */
    ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *playerMesh = ResourceManager::loadAndFetchMesh("../meshes/player.fbx");
    // references are from the the build folder

    for(int i=1;i<5;i++){
        player = new GameObject(playerMesh);
        player->setLocation(make_vector(0.50f, 0.50f,0.50f-i*5.0f));
        StandardRenderer *stdrenderer = new StandardRenderer(playerMesh, player, standardShader);
        player->addRenderComponent(stdrenderer);
        player->setDynamic(true);

        /* Add the player to the scene */
        addShadowCaster(player);
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
    addShadowCaster(player);

    player->addComponent(camera);

    /* Load player mesh and attach it to the player GameObject */
    Mesh *FloorMesh = ResourceManager::loadAndFetchMesh("../meshes/ground.obj");
    // references are from the the build folder


    GameObject* floor = new GameObject(FloorMesh);
    floor->setLocation(make_vector(0.0f, 0.0f,0.0f));
    StandardRenderer *floorrenderer = new StandardRenderer(FloorMesh, floor, standardShader);
    floor->addRenderComponent(floorrenderer);
    floor->setDynamic(true);

    GameObject* hud = new GameObject();
    hud->addRenderComponent(new ActionMenu());
    addTransparentObject(hud);

    /* Add the player to the scene */
    addShadowCaster(floor);

    createLight();

}

void ExploreScene::createLight() {

    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.50f,0.50f,0.50f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);

}

Camera* ExploreScene::getCamera() {
    return camera;
}

bool ExploreScene::changeScene() {
    return false;
}

void ExploreScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    checkKeyboardKeys();
}

void ExploreScene::initKeyBindings(){
    ControlsManager* cm = ControlsManager::getInstance();
    cm->clearBindings();
    cm->addBinding(MOVE_H,{new KeyboardButton(sf::Keyboard::D,sf::Keyboard::A)});
    cm->addBinding(MOVE_V,{new KeyboardButton(sf::Keyboard::W,sf::Keyboard::S)});

}

void ExploreScene::checkKeyboardKeys(){
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