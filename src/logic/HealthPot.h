//
// Created by simon on 2016-10-02.
//

#ifndef BUBBAROGUEFORT_HEALTHPOT_H
#define BUBBAROGUEFORT_HEALTHPOT_H


#include "InventoryItem.h"

class HealthPot : public InventoryItem{
public:
    HealthPot(int healthToGain);

private:
    virtual void affect(Bandit *usedOn);


protected:
    int healthToGain;

};


#endif //BUBBAROGUEFORT_HEALTHPOT_H
