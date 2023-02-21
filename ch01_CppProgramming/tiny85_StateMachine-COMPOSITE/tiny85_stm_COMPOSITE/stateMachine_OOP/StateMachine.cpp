#include "StateMachine.h"

StateMachine::StateMachine(State* initial) {
    initial_state = initial;
}

void StateMachine::start(State* state)
{
    current_state = (state) ? state : initial_state;
    current_state->handlers.in();
	if(current_state->stm_node.inner_stm) 
		current_state->stm_node.inner_stm->start();
}

void StateMachine::stop()
{
	current_state->handlers.out();
	current_state = nullptr;
}

void StateMachine::check_event() {
	for (unsigned i = 0; i < current_state->connections.SIZE; i++)
	{
		if (current_state 
			&& current_state->connections.buff[i]->trans->cond())
		{
			//если состояние имеет внутреннюю StateMachine, то ее останавливаем
			if( current_state->stm_node.inner_stm ) 
				current_state->stm_node.inner_stm->stop();
			
			//выходим из состояния
			current_state->handlers.out();
			
			//осуществляем переход в новое состояние по назначенной транзакции
			current_state->connections.buff[i]->trans->act();
			current_state = current_state->connections.buff[i]->to_State;
			
			//если новое состояние находится в рамках этой же StateMachine,
			//то входим в состояние
			if( current_state->stm_node.upper_stm == this) 
				current_state->handlers.in();
				if( current_state->stm_node.inner_stm ) 
					current_state->stm_node.inner_stm->start(current_state);
				
			//иначе, останавливаем текущюю StateMachine и 
			//запускаем новую, согласно нового состояния
			else 
			{
				State* tmp = current_state;
				stop();
				if(tmp) tmp->stm_node.upper_stm->start(tmp);
			}
		}
	}
}
