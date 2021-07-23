#pragma once

using condition_func = bool (*)();
using action_func = void (*)();

struct Transaction {
	const char* _name;
	condition_func _cond;
	action_func _act;

	Transaction(const char* name, condition_func cond, action_func act);
};

