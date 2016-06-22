#include "IComponent.h"

#ifndef BUBBAROGUEFORT_HEALTHCOMPONENT_H
#define BUBBAROGUEFORT_HEALTHCOMPONENT_H


class HealthComponent : public IComponent {
public:
    HealthComponent(int maxHealth);

    void addToHealth(int modifier);
    void setHealth(int newHealth);
    void setMaxHealth(int newMaxHealth);

    void update(float dt);
    int getHealth();

private:
    int maxHealth;
    int health;
};


#endif //BUBBAROGUEFORT_HEALTHCOMPONENT_H
