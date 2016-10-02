//
// Created by simon on 2016-10-01.
//

#ifndef BUBBAROGUEFORT_CREWMEMBER_H
#define BUBBAROGUEFORT_CREWMEMBER_H


#include "Bandit.h"

class CrewMember : public Bandit{
public:

    enum CrewType {DOG,KID};

    CrewMember(std::string name, int maxHealth, CrewType crewType);
    CrewMember(string name, int maxHealth, CrewType crewType, Stats *stats, unordered_map<string, Attack> *attacks);

    CrewType getCrewType();

private:
    CrewType crewType;
};


#endif //BUBBAROGUEFORT_CREWMEMBER_H
