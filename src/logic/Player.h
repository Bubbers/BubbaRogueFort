//
// Created by simon on 2016-06-24.
//

#ifndef BUBBAROGUEFORT_PLAYER_H
#define BUBBAROGUEFORT_PLAYER_H

#include <vector>
#include "Bandit.h"

class Player {
public:
    Player();
    std::vector<Bandit*>* getFighters();

private:
    std::vector<Bandit*>* fighters;

};


#endif //BUBBAROGUEFORT_PLAYER_H
