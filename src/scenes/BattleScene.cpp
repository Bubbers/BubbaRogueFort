//
// Created by johan on 2016-06-22.
//

#include <Globals.h>
#include <ResourceManager.h>
#include <StandardRenderer.h>
#include <constants.h>
#include <iostream>
#include "BattleScene.h"
#include "../level/LevelFileReader.h"
#include "../components/PlayerCamera.h"
#include "../ui/ActionMenu.h"
#include "../logic/KidBandit.h"
#include "constants.h"


BattleScene::BattleScene() {
    scene = LevelFileReader::read("../levels/battle.level", this);
    enemies = new vector<Enemy*>();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);
    createLight();

    for(int i = 0; i < 4; i++) {
        Mesh *monsterMesh = ResourceManager::loadAndFetchMesh("../meshes/monster.obj");
        GameObject *monster = new GameObject(monsterMesh);
        monster->setLocation(make_vector(-10.0f, 0.0f, i * 4.0f - 6.0f));
        monster->setRotation(make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), M_PI / 2));
        Enemy* enemy = new Enemy();
        monster->addComponent(enemy);
        enemies->insert(enemies->end(),enemy);

        ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);
        StandardRenderer *stdrenderer = new StandardRenderer(monsterMesh, monster, standardShader);
        monster->addRenderComponent(stdrenderer);
        scene->addShadowCaster(monster);
    }



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
    if(playersTurnElseEnemies) {
        pair<string, Bandit *> *action = hud->pollAction();
        if (action != nullptr) {
            playersTurnElseEnemies = false;
            Enemy* enemy = enemies->back();
            enemy->takeDamage(action->second->performAttack(action->first));
            if(!enemy->isAlive()) {
                cout << "Enemy " << enemy->getName() << " died.\n";
                enemies->pop_back();
                if(enemies->size() == 0)
                    requestSceneChange(EXPLORE_SCENE);
            }else
                cout << "Enemy " << enemy->getName() << " has " << enemy->getHealth() << " health left.\n";
        }
    }else{
        Enemy* attacker = enemies->at(getRandomIndex(enemies->size()));
        int targetI = getRandomIndex(player->getFighters()->size());
        Bandit* target = player->getFighters()->at(targetI);
        target->takeDamage(attacker->performAttack(attacker->getArbitraryAttack()));
        if(target->isAlive()) {
            cout << "Member " << target->getName() << " has " << target->getHealth() << " health left.\n";
        } else{
            cout << "Member " << target->getName() << " has died. His actions will be remembered. Like that time when he made a pie.\n";
            player->getFighters()->erase(player->getFighters()->begin() + targetI);
            hud->updateBanditButtons();

        }
        playersTurnElseEnemies = true;
    }
}

int BattleScene::getRandomIndex(int size) {

    int index = round((float)rand()/RAND_MAX*size);
    if(index == size)
        index--;
    return index;
}

void BattleScene::sceneEntry(Player *player, Camera *camera) {
    this->player = player;
    placePlayerFighters();
    GameObject* hudObj = new GameObject();
    hud = new ActionMenu(player->getFighters());
    hudObj->addRenderComponent(hud);
    scene->addTransparentObject(hudObj);

}

void BattleScene::placePlayerFighters() {
    int i = 0;
    for(Bandit* fighter : *(player->getFighters())){
        Mesh *fighterMesh = ResourceManager::loadAndFetchMesh("../meshes/bubba.obj");
        GameObject *fighterObj = new GameObject(fighterMesh);
        fighterObj->setLocation(make_vector(10.0f, 0.0f, i++ * 4.0f - 6.0f));
        fighterObj->setRotation(make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), -M_PI / 2));
        fighterObj->addComponent(fighter);

        ShaderProgram* standardShader = ResourceManager::getShader(SIMPLE_SHADER_NAME);
        StandardRenderer *stdrenderer = new StandardRenderer(fighterMesh, fighterObj, standardShader);
        fighterObj->addRenderComponent(stdrenderer);
        scene->addShadowCaster(fighterObj);

    }
}