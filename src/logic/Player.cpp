//
// Created by simon on 2016-06-24.
//

#include "Player.h"
#include "KidBandit.h"

using namespace std;

Player::Player() {
    fighters = new vector<Bandit*>();
    fighters->insert(fighters->end(),new KidBandit("Orvar"));
    fighters->insert(fighters->end(),new KidBandit("Torf"));
}

vector<Bandit*>* Player::getFighters() {
    return fighters;
}