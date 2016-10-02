//
// Created by simon on 2016-06-24.
//

#include "Player.h"
#include "KidBandit.h"
#include "Dog.h"

using namespace std;

Player::Player() {
    fighters = new vector<CrewMember*>();
    fighters->insert(fighters->end(),new KidBandit("Orvar"));
    fighters->insert(fighters->end(),new KidBandit("Torf"));
    fighters->insert(fighters->end(),new Dog("Brasken"));
}

vector<CrewMember*>* Player::getFighters() {
    return fighters;
}