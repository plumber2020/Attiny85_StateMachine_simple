#pragma once
#include "Transaction.h"

struct State;

struct Connection {
	Transaction* _trans;
	State* _to;

	Connection(Transaction* trans, State* to);
};
