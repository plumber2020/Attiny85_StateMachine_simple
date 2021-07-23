#include "Print.h"
#include <iostream>

#ifdef PRINT_DEBUG

void Print::print_StateMachineTable(StateMachine const& stm) {

	int w1 = 15, w2 = 45;
	const char* blank_line = 
		"-------------------------------------------------------------------------------------\n";
	const char* format_line = "| %-*s | %-*s | %-*s |\n";

	std::printf(blank_line);
	std::printf(format_line,
		w1, "STATE_from",
		w2, "TRANSACTION",
		w1, "STATE_to");
	std::printf(blank_line);

	for (unsigned i = 0; i < stm.CONNS_SIZE; i++)
	{
		std::printf(format_line,
			w1, stm._conns[i]->_from->_name,
			w2, stm._conns[i]->_trans->_name,
			w1, stm._conns[i]->_to->_name);
	}

	std::printf(blank_line);



}

void Print::print_currentState(StateMachine const& stm) {
	std::printf("currentState = %s", stm._current_state->_name);
}




#endif // PRINT_DEBUG
