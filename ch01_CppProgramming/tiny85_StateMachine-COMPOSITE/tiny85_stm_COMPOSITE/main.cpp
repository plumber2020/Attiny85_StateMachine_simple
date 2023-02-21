/*
 * tiny85_stm_VIRTUAL_.cpp
 *
 * Created: 29.01.2023 3:15:34
 * Author : abram
 */ 

#include "compiler.h"
#include "driver_init.h"
#include "stateMachine_OOP/StateMachine.h"
#include <avr/interrupt.h>


volatile uint16_t stm_0_tic = 0;
volatile uint16_t stm_1_tic = 0;
volatile bool	  tic_flag  = 0;


///////////////////////////////////////////////////////////
//	STATE SETTING	///////////////////////////////////////

enum StateNames {STATE_SUPER, STATE_RED, STATE_YELLOW, STATE_GREEN};
	
State state_0(STATE_SUPER);
State state_1(STATE_RED);
State state_2(STATE_YELLOW);
State state_3(STATE_GREEN);

#define STATE0_PERIOD_msec		420		//LED_SUPER (RED+YELLOW)
#define STATE1_PERIOD_msec		100		//LED_RED
#define STATE2_PERIOD_msec		30		//LED_YELLOW
#define STATE3_PERIOD_msec		420		//LED_GREEN

void in_0 ()	{ PIN_SET_HIGH(LED_SUPER);	stm_0_tic = 0;	}
void out_0()	{ PIN_SET_LOW(LED_SUPER);					}

void in_1()		{ PIN_SET_HIGH(LED_RED);	stm_1_tic = 0;	}
void out_1()	{ PIN_SET_LOW(LED_RED);						}

void in_2()		{ PIN_SET_HIGH(LED_YELLOW);	stm_1_tic = 0;	}
void out_2()	{ PIN_SET_LOW(LED_YELLOW);					}

void in_3()		{ PIN_SET_HIGH(LED_GREEN);	stm_0_tic = 0;	}
void out_3()	{ PIN_SET_LOW(LED_GREEN);					}
	
///////////////////////////////////////////////////////////
//	TIC SETTING	///////////////////////////////////////////

void TMR1_Interrupt() { ++stm_0_tic; ++stm_1_tic; tic_flag = 1; }
bool stm_0_timeout(uint16_t delay_ms) { return stm_0_tic*TMR1_INTERRUPT_PERIOD_ms >= delay_ms; }
bool stm_1_timeout(uint16_t delay_ms) { return stm_1_tic*TMR1_INTERRUPT_PERIOD_ms >= delay_ms; }

///////////////////////////////////////////////////////////
//	TRANS SETTING	///////////////////////////////////////

void action0_tic_reset()	{ stm_0_tic = 0; }
void action1_tic_reset()	{ stm_1_tic = 0; }

bool condition_0() { 
	return stm_0_timeout(STATE0_PERIOD_msec);
	 }
Transaction tr0(condition_0,action0_tic_reset);

bool condition_1() { 
	return stm_1_timeout(STATE1_PERIOD_msec); 
	}
Transaction tr1(condition_1,action1_tic_reset);

bool condition_2() {
	return stm_1_timeout(STATE2_PERIOD_msec);
}
Transaction tr2(condition_2,action1_tic_reset);

bool condition_3() {
	return stm_0_timeout(STATE3_PERIOD_msec);
}
Transaction tr3(condition_3,action0_tic_reset);

///////////////////////////////////////////////////////////
//	CONNS SETTING	///////////////////////////////////////

Connection conn_of_state_0(&tr0, &state_3);
Connection conn_of_state_1(&tr1, &state_2);
Connection conn_of_state_2(&tr2, &state_1);
Connection conn_of_state_3(&tr3, &state_0);

///////////////////////////////////////////////////////////
//	MACHINE SETTING	///////////////////////////////////////

StateMachine stm[2] {&state_0,&state_1};


int main(void)
{
	system_init();
	 
	///////////////////////////////////////////////////////////

	state_0.set_function(in_0,out_1);
	state_1.set_function(in_1,out_1);
	state_2.set_function(in_2,out_2);
	state_3.set_function(in_3,out_3);
	
	Connection*	conns_ARRAY[4];
	conns_ARRAY[0] = &conn_of_state_0;
	state_0.set_connections(&conns_ARRAY[0],1);
	
	conns_ARRAY[1] = &conn_of_state_1;
	state_1.set_connections(&conns_ARRAY[1],1);
	
	conns_ARRAY[2] = &conn_of_state_2;
	state_2.set_connections(&conns_ARRAY[2],1);
	
	conns_ARRAY[3] = &conn_of_state_3;
	state_3.set_connections(&conns_ARRAY[3],1);
			
	state_0.set_upper_stm(&stm[0]);
	state_1.set_upper_stm(&stm[1]);
	state_2.set_upper_stm(&stm[1]);
	state_3.set_upper_stm(&stm[0]);
	
	state_0.set_inner_stm(&stm[1]);
	
	stm[0].start();
	/////////////////////////////////////////////////////////
	
	TMR1_Start();
	sei();

	while (1) 
	{
		if(tic_flag) {
			stm[0].check_event();
			stm[1].check_event();
			
			tic_flag  = 0;
			PIN_SET_TOGGLE(LED_TIC_COUNTER);
		}
	}
}

