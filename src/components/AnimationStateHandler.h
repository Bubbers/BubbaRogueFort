#pragma once

#include "IComponent.h"
#include "scenes/AnimationState.h"
#include <memory>
#include <iostream>

class AnimationStateHandler : public IComponent {
public:

    AnimationStateHandler(std::shared_ptr<AnimationState> animationState);
    ~AnimationStateHandler() = default;

    void update(float dt) override;
    void onDeath() override;
private:
    std::shared_ptr<AnimationState> animationState;;
};
