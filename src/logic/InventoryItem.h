//
// Created by simon on 2016-10-02.
//

#ifndef BUBBAROGUEFORT_INVENTORYITEM_H
#define BUBBAROGUEFORT_INVENTORYITEM_H

#include <string>

class Bandit;

class InventoryItem {

public:
    enum Target {FRIENDLY,HOSTILE};
    virtual void affect(Bandit *usedOn) = 0;
    InventoryItem(Target target, std::string name);

    Target getTarget();
    std::string getName();

private:
    Target target;
    std::string name;

};


#endif //BUBBAROGUEFORT_INVENTORYITEM_H
