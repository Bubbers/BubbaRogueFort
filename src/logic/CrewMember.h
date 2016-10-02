#pragma once

#include "Bandit.h"

class CrewMember : public Bandit{
public:

    enum CrewType {DOG, KID};

    CrewMember(std::string name, int maxHealth, CrewType crewType);
    CrewMember(std::string name, int maxHealth, CrewType crewType,
               Stats *stats, std::unordered_map<std::string, Attack> *attacks);

    CrewType getCrewType();

private:
    CrewType crewType;
};
