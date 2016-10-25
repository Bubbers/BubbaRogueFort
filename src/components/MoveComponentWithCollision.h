#pragma once

#include <MoveComponent.h>


class MoveComponentWithCollision : public MoveComponent {

public:
    MoveComponentWithCollision();
    virtual void beforeCollision(std::shared_ptr<GameObject> collider) override ;
    virtual void duringCollision(std::shared_ptr<GameObject> collider) override ;
    virtual void afterCollision(std::shared_ptr<GameObject> collider) override ;

    virtual void update(float dt) override;


private:
    bool isColliding = false;

    void initKeyBindings();
    void checkKeyboardKeys();

    const float SQRT_2 = sqrtf(2);
};
