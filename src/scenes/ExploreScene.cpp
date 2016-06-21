//
// Created by simon on 2016-06-21.
//

#include <PerspectiveCamera.h>
#include <ResourceManager.h>
#include <constants.h>
#include <StandardRenderer.h>
#include <Globals.h>
#include "ExploreScene.h"

ExploreScene::ExploreScene() {

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PerspectiveCamera(
            make_vector(10.0f, 10.0f, 10.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f, 1.0f, 0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);

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
    addShadowCaster(player);

}

Camera* ExploreScene::getCamera() {
    return camera;
}

bool ExploreScene::changeScene() {
    return false;
}