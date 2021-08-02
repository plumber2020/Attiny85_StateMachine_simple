#pragma once

using condition_func = bool (*)();
using action_func = void (*)();

struct Transaction {
	unsigned _id;
	condition_func _cond;
	action_func _act;

	Transaction(condition_func cond, action_func act);
};

