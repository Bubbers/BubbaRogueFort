#pragma once

#include <MoveComponent.h>


class MoveComponentWithCollision : public MoveComponent {

public:
    MoveComponentWithCollision(GameObject* gameObject);
    virtual void beforeCollision(GameObject* collider) override ;
    virtual void duringCollision(GameObject* collider) override ;
    virtual void afterCollision(GameObject* collider) override ;

    virtual void update(float dt) override;


private:
    bool isColliding = false;

    void initKeyBindings();
    void checkKeyboardKeys();

    const float SQRT_2 = sqrtf(2);
};
