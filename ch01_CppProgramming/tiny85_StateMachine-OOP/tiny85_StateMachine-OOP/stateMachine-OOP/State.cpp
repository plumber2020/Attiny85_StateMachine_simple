#include "State.h"

State::State(state_func in, state_func out) :
	_in(in), _out(out)
{
	static unsigned id = 0; _id = id++;
}

void State::connects(Connection** conns, unsigned SIZE)
{
	_connectionArray = conns;
	_connectionSIZE = SIZE;
}
