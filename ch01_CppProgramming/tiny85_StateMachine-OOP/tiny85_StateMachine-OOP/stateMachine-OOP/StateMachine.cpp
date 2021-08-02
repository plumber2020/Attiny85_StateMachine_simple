#include "StateMachine.h"
#include "Transaction.h"
#include "Connection.h"

void StateMachine::set_initialState(State* state) {
    _current_state = state;
	_current_state->_in();
}

void StateMachine::check_event() {
	for (unsigned i = 0; i < _current_state->_connectionSIZE; i++)
	{
		if ( _current_state->_connectionArray[i]->_trans->_cond())
		{
			_current_state->_out();
			_current_state->_connectionArray[i]->_trans->_act();
			_current_state = _current_state->_connectionArray[i]->_to;
			_current_state->_in();
			return;
		}
	}
}
