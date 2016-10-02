#pragma once

class AnimationState {

public:
    AnimationState() { state = State::NO_ANIM; }

    enum State {
    NO_ANIM,
    UNRESOLVED,
    RUNNING
    };

    AnimationState::State state;

};
