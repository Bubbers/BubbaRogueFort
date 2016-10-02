//
// Created by simon on 2016-10-02.
//

#ifndef BUBBAROGUEFORT_INVENTORYITEM_H
#define BUBBAROGUEFORT_INVENTORYITEM_H

class Bandit;

class InventoryItem {

public:
    enum Target {FRIENDLY,HOSTILE};
    virtual void affect(Bandit &usedOn) = 0;
    InventoryItem(Target target);

private:
    Target target;

};


#endif //BUBBAROGUEFORT_INVENTORYITEM_H
