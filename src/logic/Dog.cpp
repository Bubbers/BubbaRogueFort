//
// Created by simon on 2016-10-01.
//

#include "Dog.h"

Dog::Dog(std::string name) : CrewMember(name, 10, CrewType::DOG) {

    stats = new Stats(5);
    attacks = new unordered_map<std::string,Attack>();
    attacks->insert(pair<std::string,Attack>("bite",punch()));

}
