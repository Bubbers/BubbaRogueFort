//
// Created by simon on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_BANDIT_H
#define BUBBAROGUEFORT_BANDIT_H

#include <unordered_map>
#include <unordered_set>
#include <IComponent.h>
#include "Attack.h"

class Bandit : public IComponent {

public:
    std::unordered_set<std::string> getAttacks();
    AttackResult performAttack(std::string);
    void takeDamage(AttackResult damage);
    std::string getName();
    virtual void update(float dt) override {};
    virtual bool isAlive();
    virtual int getHealth();
    virtual bool equals(Bandit* other);

protected:
    Bandit(std::string name, Stats* stats, std::unordered_map<std::string,Attack>* attacks);
    Bandit(std::string name);

    Stats* stats;
    std::unordered_map<std::string,Attack>* attacks;

    int health;
    std::string name;

};


#endif //BUBBAROGUEFORT_BANDIT_H
