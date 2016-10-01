#include <ControlsManager.h>
#include <SFML/Window/Keyboard.hpp>
#include <KeyboardButton.h>
#include "MoveComponentWithCollision.h"
#include "../controls.h"

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

    if(cs_H.isActive() && cs_V.isActive())
    {
        if(cs_H.getValue() > 0 && cs_V.getValue() < 0)
        {
            this->setVelocity(make_vector(0.01f, 0.00f, 0.01f) / SQRT_2);
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI / 4));
        }
        else if(cs_H.getValue() > 0 && cs_V.getValue() > 0)
        {
            this->setVelocity(make_vector(0.01f, 0.00f, -0.01f) / SQRT_2);
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, (3 * M_PI) / 4));
        }
        else if(cs_H.getValue() < 0 && cs_V.getValue() < 0)
        {
            this->setVelocity(make_vector(-0.01f, 0.0f, 0.01f) / SQRT_2);
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI / -4));
        }
        else{
            this->setVelocity(make_vector(-0.01f, 0.0f, -0.01f) / SQRT_2);
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, (-3 * M_PI) / 4));
        }
    }
    else if(cs_H.isActive())
    {
        if(cs_H.getValue() > 0)
        {
            this->setVelocity(make_vector(0.01f, 0.0f, 0.0f));
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI / 2));
        }
        else{
            this->setVelocity(make_vector(-0.01f, 0.0f, 0.0f));
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI / -2));
        }
    }
    else if(cs_V.isActive())
    {
        if(cs_V.getValue() < 0) {
            this->setVelocity(make_vector(0.0f, 0.0f, 0.01f));
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI * -2));
        }
        else{
            this->setVelocity(make_vector(0.0f, -0.0f, -0.01f));
            owner->setRotation(make_quaternion_axis_angle(UP_VECTOR, M_PI / -1.0f));
        }
    }
    else if(!cs_H.isActive() && !cs_V.isActive()){
        this->setVelocity(make_vector(0.0f, 0.0f, 0.0f));
    }
}
