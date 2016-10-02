#pragma once

#include "RogueFortScene.h"
#include "ui/ActionMenu.h"
#include "logic/Enemy.h"
#include "logic/KidBandit.h"
#include "scenes/AnimationState.h"
#include <memory>

class BattleScene : public RogueFortScene {
public:
    BattleScene();

    virtual Camera* getCamera();
    virtual void update(float dt, std::vector<GameObject*> *toDelete);
    virtual void resize(int x, int y);

    virtual void sceneEntry(Player* player, Camera* camera);

private:

    void createLight();
    int getRandomIndex(int size);
    void placePlayerFighters();
    void deleteEnemyFromList(Enemy* enemy);
    Enemy* getRandomEnemy();

    typedef std::unordered_map<Enemy*,GameObject*,Bandit::BanditHash> enemyMap;
    enemyMap* enemies;
    Player* player;

    ActionMenu *hud;
    Camera* camera;

    bool playersTurnElseEnemies = true;

    std::shared_ptr<AnimationState> animationState = std::make_shared<AnimationState>();

    std::function<void()> doAfterAnimation;
};

