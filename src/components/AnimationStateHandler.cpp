#include "AnimationStateHandler.h"

AnimationStateHandler::AnimationStateHandler(std::shared_ptr<AnimationState> animationState):
    animationState(animationState) {
    animationState->state = AnimationState::State::RUNNING;
}

void AnimationStateHandler::update(float dt) {
}

void AnimationStateHandler::onDeath() {
    animationState->state = AnimationState::State::UNRESOLVED;
}
