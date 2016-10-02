//
// Created by simon on 2016-10-02.
//

#include "HealthPot.h"
#include "Bandit.h"

HealthPot::HealthPot(int healthToGain) : healthToGain(healthToGain), InventoryItem(Target::FRIENDLY) {}

void HealthPot::affect(Bandit &usedOn) {
    usedOn.setHealth(usedOn.getHealth() + healthToGain);
}
