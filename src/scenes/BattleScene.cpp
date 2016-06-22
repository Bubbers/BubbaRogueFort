//
// Created by johan on 2016-06-22.
//

#include <Globals.h>
#include <ResourceManager.h>
#include <StandardRenderer.h>
#include <constants.h>
#include "BattleScene.h"
#include "../level/LevelFileReader.h"
#include "../components/PlayerCamera.h"
#include "../ui/ActionMenu.h"
#include "../logic/KidBandit.h"
#include "constants.h"


BattleScene::BattleScene() {
    scene = LevelFileReader::read("../levels/battle.level", this);

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);
    createLight();

    for(int i = 0; i < 4; i++) {
        Mesh *monsterMesh = ResourceManager::loadAndFetchMesh("../meshes/monkey.obj");
        GameObject *monster = new GameObject(monsterMesh);
        monster->setLocation(make_vector(-10.0f, 0.0f, i * 4.0f - 6.0f));
        monster->setRotation(make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), M_PI / 2));

        ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);
        StandardRenderer *stdrenderer = new StandardRenderer(monsterMesh, monster, standardShader);
        monster->addRenderComponent(stdrenderer);
        scene->addShadowCaster(monster);
    }

    GameObject* hudObj = new GameObject();
    vector<Bandit*>* bandits = new vector<Bandit*>();
    bandits->insert(bandits->end(),new KidBandit());
    hud = new ActionMenu(bandits);
    hudObj->addRenderComponent(hud);
    scene->addTransparentObject(hudObj);


}

void BattleScene::createLight() {

    DirectionalLight directionalLight = DirectionalLight();
    directionalLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.specularColor=make_vector(0.50f,0.50f,0.50f);
    directionalLight.ambientColor=make_vector(0.50f,0.50f,0.50f);

    directionalLight.direction=-make_vector(10.0f,10.0f,10.0f);
    scene->directionalLight = directionalLight;

    PointLight pointLight;
    pointLight.diffuseColor=make_vector(0.50f,0.50f,0.50f);
    pointLight.specularColor=make_vector(0.00f,0.00f,0.00f);
    pointLight.ambientColor=make_vector(0.050f,0.050f,0.050f);
    pointLight.position = make_vector(18.0f, 3.0f, 0.0f);
    scene->pointLights.push_back(pointLight);
}


void BattleScene::resize(int x, int y) {
}

Camera* BattleScene::getCamera() {
    return camera;
}


void BattleScene::update(float dt, std::vector<GameObject *> *toDelete) {
    RogueFortScene::update(dt,toDelete);
    pair<string,Bandit*>* action = hud->pollAction();
    if(action != nullptr){
        requestSceneChange(EXPLORE_SCENE);
    }
}
