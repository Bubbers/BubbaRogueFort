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

std::string Bandit::getName() const {
    return name;
}

Bandit::Bandit(string name, int maxHealth) : Bandit(name,maxHealth,nullptr,nullptr){ }

Bandit::Bandit(string name, int maxHealth ,Stats *stats, std::unordered_map<std::string, Attack> *attacks)
        : name(name),maxHealth(maxHealth),health(maxHealth),stats(stats),attacks(attacks){ }

void Bandit::takeDamage(AttackResult damage) {
    health -= damage.damage;
    for(function<void (int)> listener : damageListeners)
        listener(health);
    if(health <= 0)
        owner->makeDirty();
}

int Bandit::getHealth() const {
    return health;
}

bool Bandit::equals(Bandit *other) {
    if(other == nullptr)
        return false;

    return other->getName() == getName() && other->getHealth() == getHealth();
}

void Bandit::addDamageListener(std::function<void(int)> listener) {
    damageListeners.push_back(listener);
}

int Bandit::getMaxHealth() {
    return maxHealth;
}
