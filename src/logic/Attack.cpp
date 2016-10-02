//
// Created by simon on 2016-06-22.
//

#include "Attack.h"
#include "Stats.h"

Attack punch(){
    return [](Stats stats) -> AttackResult {
        return AttackResult(stats.strength);
    };
}

AttackResult::AttackResult(int damage) : damage(damage) {}
