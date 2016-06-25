//
// Created by simon on 2016-06-22.
//

#include <iostream>
#include "Bandit.h"

using namespace std;

unordered_set<string> Bandit::getAttacks() {
    unordered_set<string> keys;
    for(auto attack : *attacks){
        keys.insert(attack.first);
    }
    return keys;
}

bool Bandit::isAlive() {
    return health > 0;
}

AttackResult Bandit::performAttack(string attack) {
    auto it = attacks->find(attack);
    if(it == attacks->end())
        throw runtime_error("Couldn't find attack '" + attack + "' for bandit '" + getName() + "'.");
    return (it->second)(*stats);
}

std::string Bandit::getName() {
    return name;
}

Bandit::Bandit(string name) : Bandit(name,nullptr,nullptr){ }

Bandit::Bandit(string name,Stats *stats, std::unordered_map<std::string, Attack> *attacks) : name(name),stats(stats),attacks(attacks){ }

void Bandit::takeDamage(AttackResult damage) {
    health -= damage.damage;
    if(health <= 0)
        owner->makeDirty();
}

int Bandit::getHealth() {
    return health;
}

bool Bandit::equals(Bandit *other) {
    if(other == nullptr)
        return false;

    return other->getName() == getName() && other->getHealth() == getHealth();
}