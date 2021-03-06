
#include <Globals.h>
#include <ResourceManager.h>
#include <StandardRenderer.h>
#include <constants.h>
#include <iostream>
#include <PositioningLayout.h>
#include <HUDGraphic.h>
#include "BattleScene.h"
#include "level/LevelFileReader.h"
#include "components/PlayerCamera.h"
#include "ui/ActionMenu.h"
#include "logic/KidBandit.h"
#include "constants.h"
#include "ui/HealthBar.h"
#include "components/AnimationStateHandler.h"

#include "ParticleGenerator.h"
#include "particleEffects/CircleEffect.h"
#include "Texture.h"
#include "ResourceManager.h"

using namespace chag;
using namespace std;

BattleScene::BattleScene() {

    doAfterAnimation = [] () {};

    scene = LevelFileReader::read("../levels/battle.level", this);
    enemies = new enemyMap();

    int width = Globals::get(Globals::WINDOW_WIDTH);
    int height = Globals::get(Globals::WINDOW_HEIGHT);
    camera = new PlayerCamera(
            make_vector(0.0f, 20.0f, 20.0f),
            make_vector(0.0f, 0.0f, 0.0f),
            make_vector(0.0f,1.0f,0.0f), 45, float(width) / float(height),
            0.1f, 50000.0f);
    createLight();

    for(int i = 0; i < 4; i++) {
        std::shared_ptr<Mesh> monsterMesh = ResourceManager::loadAndFetchMesh("../meshes/monster.obj");
        GameObject *monster = new GameObject(monsterMesh);
        monster->setLocation(make_vector(-10.0f, 0.0f, i * 4.0f - 6.0f));
        monster->setRotation(make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), M_PI / 2));
        Enemy* enemy = new Enemy();
        monster->addComponent(enemy);
        enemies->insert(enemies->end(),pair<Enemy*,GameObject*>(enemy,monster));

        std::shared_ptr<ShaderProgram> standardShader = ResourceManager::loadAndFetchShaderProgram(SIMPLE_SHADER_NAME, "../shader/simple.vert", "../shader/simple.frag");
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

    switch (animationState->state) {
    case AnimationState::State::RUNNING:
        return;
    case AnimationState::State::UNRESOLVED:
        doAfterAnimation();
        animationState->state = AnimationState::State::NO_ANIM;
        break;
    default:
        break;
    }

    if(playersTurnElseEnemies) {
        ActionMenu::Action *action = hud->pollAction();

        if (action != nullptr) {
            playersTurnElseEnemies = false;
            Enemy* enemy = (Enemy*)action->target;

            AttackResult attackResult = action->performer->performAttack(action->attack);

            chag::float3 pos = enemies->find(enemy)->second->getAbsoluteLocation();

            std::shared_ptr<Camera> sharedCamera(getCamera());
            attackResult.visualEffect(pos, pos, sharedCamera, [this] (GameObject* gob) {
                gob->addComponent(new AnimationStateHandler(animationState));
                scene->addTransparentObject(gob);
            });

            doAfterAnimation = [this, enemy, attackResult] () {
                enemy->takeDamage(attackResult);

                if (!enemy->isAlive()) {
                    enemies->erase(enemy);
                    printf("%lu\n", enemies->size());
                    if (enemies->size() == 0) {
                        requestSceneChange(EXPLORE_SCENE);
                    } else {
                        hud->updateLayout();
                    }
                }
            };
        }
    } else if (enemies->size() > 0) {
        Enemy* attacker = getRandomEnemy();
        int targetI = getRandomIndex(player->getFighters()->size());
        Bandit* target = player->getFighters()->at(targetI);
        target->takeDamage(attacker->performAttack(attacker->getArbitraryAttack()));
        if(!target->isAlive()) {
            player->getFighters()->erase(player->getFighters()->begin() + targetI);
            //hud->updateFighterButtons();
        }
        playersTurnElseEnemies = true;
    }
}

Enemy* BattleScene::getRandomEnemy() {
    int i = getRandomIndex(enemies->size());
    int j = 0;
    for(auto enemy : *enemies) {
        if(i == j++) {
            return enemy.first;
        }
    }

    return nullptr;
}

int BattleScene::getRandomIndex(int size) {

    int index = round((float)rand()/RAND_MAX*size);
    if(index == size)
        index--;
    return index;
}

void BattleScene::sceneEntry(Player *player, Camera *camera) {
    this->player = player;
    GameObject* hudObj = new GameObject();
    vector<Bandit*>* enemyBandits = new vector<Bandit*>();
    for(auto enemyBandit : *enemies)
        enemyBandits->push_back(enemyBandit.first);
    hud = new ActionMenu((std::vector<Bandit*>*)player->getFighters(),enemyBandits, player->getInventory());
    hud->setWorldCamera(this->camera);
    placePlayerFighters();
    for(auto enemy : *enemies)
        hud->addRelativeLayout(enemy.second,new HealthBar(enemy.first));
    hudObj->addRenderComponent(hud);
    scene->addTransparentObject(hudObj);

}

void BattleScene::placePlayerFighters() {
    int i = 0;
    for(CrewMember* fighter : *(player->getFighters())){
        std::shared_ptr<Mesh> fighterMesh = ResourceManager::loadAndFetchMesh(fighter->getCrewType() == CrewMember::DOG ? "../meshes/dog.obj" : "../meshes/bubba.obj");
        GameObject *fighterObj = new GameObject(fighterMesh);
        fighterObj->setLocation(make_vector(10.0f, 0.0f, i++ * 4.0f - 6.0f));
        fighterObj->setRotation(make_quaternion_axis_angle(make_vector(0.0f, 1.0f, 0.0f), fighter->getCrewType() == CrewMember::DOG ? M_PI : -M_PI_2));
        fighterObj->addComponent(fighter);
        hud->addRelativeLayout(fighterObj,new HealthBar(fighter));

        std::shared_ptr<ShaderProgram> standardShader = ResourceManager::loadAndFetchShaderProgram(SIMPLE_SHADER_NAME, "../shader/simple.vert", "../shader/simple.frag");
        StandardRenderer *stdrenderer = new StandardRenderer(fighterMesh, fighterObj, standardShader);
        fighterObj->addRenderComponent(stdrenderer);
        scene->addShadowCaster(fighterObj);

    }
}
