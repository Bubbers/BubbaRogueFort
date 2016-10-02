#include <ControlsManager.h>
#include <SFML/Window/Keyboard.hpp>
#include <KeyboardButton.h>
#include "MoveComponentWithCollision.h"
#include "../controls.h"

using namespace chag;

static const float3 UP_VECTOR = make_vector(0.0f, 1.0f, 0.0f);

MoveComponentWithCollision::MoveComponentWithCollision(
    GameObject* gameObject): MoveComponent(gameObject)
{
     initKeyBindings();
}

void MoveComponentWithCollision::initKeyBindings() {
    ControlsManager* cm = ControlsManager::getInstance();
    cm->addBinding(MOVE_H, new KeyboardButton(sf::Keyboard::D,sf::Keyboard::A));
    cm->addBinding(MOVE_V, new KeyboardButton(sf::Keyboard::W,sf::Keyboard::S));
}

void MoveComponentWithCollision::duringCollision(GameObject* collider) {
}


void MoveComponentWithCollision::afterCollision(GameObject* collider) {
    isColliding = false;
}

void MoveComponentWithCollision::beforeCollision(GameObject *collider) {
    isColliding = true;
    setVelocity(-getVelocity());
}

void MoveComponentWithCollision::update(float dt) {
    if(!isColliding) {
        checkKeyboardKeys();
    }
    MoveComponent::update(dt);
}

void MoveComponentWithCollision::checkKeyboardKeys() {
    ControlsManager*  cm = ControlsManager::getInstance();
    ControlStatus   cs_H = cm->getStatus(MOVE_H);
    ControlStatus   cs_V = cm->getStatus(MOVE_V);

    if(cs_H.isActive() || cs_V.isActive()) {
        float x = cs_H.getValue() / 10000.0f;
        float y = cs_V.getValue() / 10000.0f;
        float3 vec = make_vector(x, 0.0f, -y);
        if(cs_H.isActive() && cs_V.isActive())
            vec = vec/SQRT_2;
        this->setVelocity(vec);
        float angle = y == 0.0f ? M_PI_2 : atan(std::abs(x/y));
        if(y > 0.0f)
            angle = M_PI - angle;
        if(x < 0.0f)
            angle = -angle;
        owner->setRotation(make_quaternion_axis_angle(UP_VECTOR,angle));
    } else {
        this->setVelocity(make_vector(0.0f, 0.0f, 0.0f));
    }
}
