//
// Created by johan on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_BATTLESCENE_H
#define BUBBAROGUEFORT_BATTLESCENE_H


#include "RogueFortScene.h"
#include "../ui/ActionMenu.h"
#include "../logic/Enemy.h"
#include "../logic/KidBandit.h"

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

    std::vector<std::pair<Enemy*,GameObject*>>* enemies;
    Player* player;

    ActionMenu *hud;
    Camera* camera;

    bool playersTurnElseEnemies = true;
};


#endif //BUBBAROGUEFORT_BATTLESCENE_H
