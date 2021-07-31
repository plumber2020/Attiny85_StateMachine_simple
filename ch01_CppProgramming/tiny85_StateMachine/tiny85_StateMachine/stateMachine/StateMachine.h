#pragma once
#include "State.h"
#include "Transaction.h"
#include "Connection.h"

struct StateMachine {
    State* _current_state = nullptr;
    Connection** _conns;
    const unsigned CONNS_SIZE;
    
    StateMachine(Connection** conns, const unsigned conns_SIZE);

    void set_initialState(State* state);
    void check_event();
	void print_currentState();
	
};

