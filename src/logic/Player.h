//
// Created by simon on 2016-06-24.
//

#ifndef BUBBAROGUEFORT_PLAYER_H
#define BUBBAROGUEFORT_PLAYER_H

#include <vector>
#include "CrewMember.h"

class Player {
public:
    Player();
    std::vector<CrewMember*>* getFighters();

private:
    std::vector<CrewMember*>* fighters;

};


#endif //BUBBAROGUEFORT_PLAYER_H
