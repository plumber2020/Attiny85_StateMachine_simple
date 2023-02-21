#include "State.h"
#include <string.h>


State::State(uint16_t stateID) : stateID(stateID)
{
}

void State::set_function(state_handler in, state_handler out)
{
	 handlers.in = in;
	 handlers.out = out;
}

void State::set_connections(Connection** array, uint16_t size)
{
	connections.buff = array;
	connections.SIZE = size;
}

void State::set_upper_stm(StateMachine* stm)
{
	stm_node.upper_stm = stm;
}

void State::set_inner_stm(StateMachine* stm)
{
	stm_node.inner_stm = stm;
}
