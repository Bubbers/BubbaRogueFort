//
// Created by johan on 2016-06-21.
//

#ifndef BUBBAROGUEFORT_MOVECOMPONENTWITHCOLLISION_H
#define BUBBAROGUEFORT_MOVECOMPONENTWITHCOLLISION_H


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
};


#endif //BUBBAROGUEFORT_MOVECOMPONENTWITHCOLLISION_H
