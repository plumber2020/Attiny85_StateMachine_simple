#pragma once
#include "compiler.h"
#include "Transaction.h"

struct State;

struct Connection {
	Transaction		*trans;
	State			*to_State;

	Connection(Transaction* trans, State* to);
};

