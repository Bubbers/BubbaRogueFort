#include "HealthComponent.h"
HealthComponent::HealthComponent(int maxHealth): maxHealth(maxHealth), health(maxHealth) { }

void HealthComponent::setHealth(int newHealth) {
    health = newHealth;
}

void HealthComponent::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
}

void HealthComponent::addToHealth(int modifier) {
    health += modifier;
}

void HealthComponent::update(float dt) {
    if (health <= 0) {
        owner->makeDirty();
    }
}

