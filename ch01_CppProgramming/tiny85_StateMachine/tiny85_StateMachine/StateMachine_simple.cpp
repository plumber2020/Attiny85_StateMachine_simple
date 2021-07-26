#include "StateMachine_simple.hpp"


void StateMachine_Initialize() 
{
    stm.set_initial(&state_Y, p_conn);
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


