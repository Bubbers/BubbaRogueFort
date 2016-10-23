//
// Created by simon on 2016-10-02.
//

#include "InventoryItem.h"


InventoryItem::InventoryItem(InventoryItem::Target target, std::string name) : target(target), name(name){}

std::string InventoryItem::getName() {
    return name;
}

InventoryItem::Target InventoryItem::getTarget() {
    return target;
}
