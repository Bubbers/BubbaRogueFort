//
// Created by simon on 2016-06-22.
//

#include "Enemy.h"

using namespace std;

Enemy::Enemy() : Bandit("Enemy ", 2){
    static int id = 0;
    name.append(to_string(++id));
    stats = new Stats(3);
    attacks = new unordered_map<string,Attack>();
    attacks->insert(pair<string,Attack>("punch",punch()));
}

string Enemy::getArbitraryAttack() {
    return "punch";
}