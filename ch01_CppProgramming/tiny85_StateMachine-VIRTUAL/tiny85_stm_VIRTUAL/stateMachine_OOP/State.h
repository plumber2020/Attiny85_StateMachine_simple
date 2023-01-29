#pragma once
#include "compiler.h"
#include "Connection.h"

using state_func = void (*)();

struct StateMachine;

struct State
{	
	struct ConnectionNode {	Connection** buff; uint16_t SIZE; };
	
	char			name[8] = {};
	state_func		in;
	state_func		out;
	ConnectionNode	connections = {};

	StateMachine*	upper_stm = nullptr;
	StateMachine*	inner_stm = nullptr;
	
	State() = delete;
	State(State const&) = delete;
	State& operator=(State const&) = delete;
	
	State(char const*);
	
	void set_function(state_func in, state_func out);
	void set_connections(Connection** array, uint16_t size);
	void set_upper_stm(StateMachine*);
	void set_inner_stm(StateMachine*);
};
