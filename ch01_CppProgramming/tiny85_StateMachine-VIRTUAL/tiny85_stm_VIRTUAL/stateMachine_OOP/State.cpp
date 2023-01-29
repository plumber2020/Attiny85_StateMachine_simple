#include "State.h"
#include <string.h>


State::State(char const* nameID)
{
	strncpy(name, nameID, 8);
}

void State::set_function(state_func in_func, state_func out_func)
{
	 in = in_func;
	 out = out_func;
}

void State::set_connections(Connection** array, uint16_t size)
{
	connections.buff = array;
	connections.SIZE = size;
}

void State::set_upper_stm(StateMachine* stm)
{
	upper_stm = stm;
}

void State::set_inner_stm(StateMachine* stm)
{
	inner_stm = stm;
}
