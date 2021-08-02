#pragma once
#include "State.h"

struct StateMachine {
    State* _current_state = nullptr;
    
    StateMachine() = default;

    void set_initialState(State* state);
    void check_event();
};

