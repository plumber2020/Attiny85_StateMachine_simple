#pragma once
#include "Connection.h"

using state_func = void (*)();

struct State {
	unsigned _id;
	state_func _in, _out;
	
    Connection** _connectionArray;
    unsigned _connectionSIZE;
	
	State(state_func in, state_func out);
	void connects(Connection** conns, unsigned SIZE);
};

