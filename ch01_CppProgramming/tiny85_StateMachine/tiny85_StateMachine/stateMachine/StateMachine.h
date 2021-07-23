#pragma once
#include "State.h"
#include "Transaction.h"
#include "Connection.h"

struct StateMachine {
    State* _current_state = nullptr;
    Connection** _conns;
    const unsigned CONNS_SIZE;
    
    StateMachine(const unsigned conns_SIZE);

    void set_initial(State* state, Connection** conns);
    void check_event();
	void print_currentState();
	
};

