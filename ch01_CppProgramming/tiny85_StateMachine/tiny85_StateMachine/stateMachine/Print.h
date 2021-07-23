#pragma once
#include "State.h"
#include "Transaction.h"
#include "Connection.h"
#include "StateMachine.h"

#define PRINT_DEBUG


struct Print {
	void print_StateMachineTable(StateMachine const& stm);
	void print_currentState(StateMachine const& stm);
};



