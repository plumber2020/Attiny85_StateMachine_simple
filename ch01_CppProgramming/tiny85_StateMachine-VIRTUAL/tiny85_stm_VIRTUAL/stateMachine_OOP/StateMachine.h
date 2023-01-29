#pragma once
#include "State.h"

struct StateMachine {
    State* initial_state = nullptr;
    State* current_state = nullptr;

    StateMachine(State* initial);
	
    void start(State* state = nullptr);
    void stop();
    void check_event();
};

