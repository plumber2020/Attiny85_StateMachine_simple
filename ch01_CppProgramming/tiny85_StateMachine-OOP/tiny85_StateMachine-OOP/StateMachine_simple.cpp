#include "StateMachine_simple.hpp"


void StateMachine_Initialize() 
{
	state_R.connects(p_connections_fromR, 1);
	state_Y.connects(p_connections_fromY, 2);
	state_G.connects(p_connections_fromG, 1);
	state_B.connects(p_connections_fromB, 2);
    
	stm.set_initialState(&state_Y);
}

inline bool TMR1_TimeOUT(unsigned delay_ms) {
	return (tic_counter * TMR1_INTERRUPT_PERIOD_ms) >= delay_ms;
}

void TMR1_Interrupt() {	
	++tic_counter;
	tic_counter_changed_flag = true;
	PIN_SET_HIGH(LED_TIC_COUNTER);
}

void StateMachine_eventCHECKING() {
	if(tic_counter_changed_flag) {
		tic_counter_changed_flag = false;
	
		stm.check_event();	
		if(tic_counter==0) PIN_SET_HIGH(LED_TIC_RESET);
	}
		
	PIN_SET_LOW(LED_TIC_COUNTER);
	PIN_SET_LOW(LED_TIC_RESET);
}


