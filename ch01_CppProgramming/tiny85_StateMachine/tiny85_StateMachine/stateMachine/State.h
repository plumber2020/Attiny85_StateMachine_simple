#pragma once

using state_func = void (*)();

struct State {
	const char* _name;
	unsigned _id;
	state_func _in, _out;

	State(const char* name, state_func in, state_func out);
};

