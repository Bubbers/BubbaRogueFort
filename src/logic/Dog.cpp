#include "Dog.h"
#include "Stats.h"

Dog::Dog(std::string name) : CrewMember(name, 10, CrewType::DOG) {

    stats = new Stats(5);
    attacks = new std::unordered_map<std::string, Attack>();
    attacks->insert(std::pair<std::string, Attack>("bite", punch()));

}
