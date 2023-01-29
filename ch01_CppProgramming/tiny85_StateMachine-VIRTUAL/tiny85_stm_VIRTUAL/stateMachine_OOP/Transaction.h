#pragma once
#include "compiler.h"

using condition_func = bool (*)();
using action_func = void (*)();

struct Transaction {
	condition_func	cond;
	action_func		act;

	Transaction(condition_func cond, action_func act);
};

