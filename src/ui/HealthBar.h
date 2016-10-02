//
// Created by simon on 2016-10-01.
//

#ifndef BUBBAROGUEFORT_HEALTHBAR_H
#define BUBBAROGUEFORT_HEALTHBAR_H

#include "PositioningLayout.h"

class Bandit;

class HealthBar : public PositioningLayout {
public:
    HealthBar(Bandit* bandit);
    void damageTaken();

    virtual void getGLSquares(float layoutXPos, float layoutYPos, float layoutWidth, float layoutHeight,
                              std::map<std::string, IHudDrawable *> *map) override;

protected:
    Bandit* bandit;
    PositioningLayout* bar;
    bool dead = false;

};


#endif //BUBBAROGUEFORT_HEALTHBAR_H
