#pragma once
#include "State.h"
#include "Transaction.h"

struct Connection {
	State* _from;
	Transaction* _trans;
	State* _to;

	Connection(State* from, Transaction* trans, State* to);
	
	static unsigned count;
};
