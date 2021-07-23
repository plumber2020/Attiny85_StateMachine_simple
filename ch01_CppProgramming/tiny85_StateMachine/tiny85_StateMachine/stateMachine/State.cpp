#include "State.h"

State::State(const char* name, state_func in, state_func out) :
	_name(name), _in(in), _out(out)
{
	static unsigned id = 0; _id = id++;
}
