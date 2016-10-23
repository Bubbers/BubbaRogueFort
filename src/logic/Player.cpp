//
// Created by simon on 2016-06-24.
//

#include "Player.h"
#include "KidBandit.h"
#include "Dog.h"
#include "HealthPot.h"

using namespace std;

Player::Player() {
    fighters = new vector<CrewMember*>();
    fighters->insert(fighters->end(),new KidBandit("Orvar"));
    fighters->insert(fighters->end(),new KidBandit("Torf"));
    fighters->insert(fighters->end(),new Dog("Brasken"));
    inventory = new vector<InventoryItem*>();
    inventory->push_back(new HealthPot(3));
}

vector<CrewMember*>* Player::getFighters() {
    return fighters;
}

std::vector<InventoryItem*>* Player::getInventory() {
    return inventory;
}