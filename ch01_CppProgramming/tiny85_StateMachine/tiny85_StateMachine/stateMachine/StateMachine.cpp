#include "StateMachine.h"

StateMachine::StateMachine(const unsigned conns_SIZE)
	: CONNS_SIZE(conns_SIZE)
{}

void StateMachine::set_initial(State* state, Connection** conns) {
    _current_state = state;
	_current_state->_in();
	_conns = conns; 
}

void StateMachine::check_event() {
	for (unsigned i = 0; i < CONNS_SIZE; i++)
	{
		if (_conns[i]->_from->_id == _current_state->_id && _conns[i]->_trans->_cond())
		{
			_conns[i]->_from->_out();
			_conns[i]->_trans->_act();
			_conns[i]->_to->_in();
			_current_state = _conns[i]->_to;
			return;
		}
	}
}
