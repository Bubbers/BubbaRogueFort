//
// Created by simon on 2016-06-22.
//

#ifndef BUBBAROGUEFORT_ATTACK_H
#define BUBBAROGUEFORT_ATTACK_H

#include <functional>
#include "Stats.h"

using namespace std;

struct AttackResult {
    int damage;
    AttackResult(int damage);
};

typedef function<AttackResult (Stats stats)> Attack;

//Sample attacks
/**
 * Does the strength as damage
 */
Attack punch();


#endif //BUBBAROGUEFORT_ATTACK_H
