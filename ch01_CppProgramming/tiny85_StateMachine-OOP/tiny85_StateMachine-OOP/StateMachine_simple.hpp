#include "StateMachine_simple.h"
#include "stateMachine-OOP/StateMachine.h"
#include "source/tmr1.h"
#include "source/pin_manager.h"


#define RED_PERIOD_msec				8000		//RED light
#define YLW_PERIOD_msec				2000		//YLW light
#define GRN_PERIOD_msec				7000		//GREEN light
#define BLINKING_MAX				5


/*
					 -----------
		 -------->	| STATE_RED |	>-------
		|			 -----------			|
		trans_YR							trans_RY
		|			 ------------			|
		 --------<	|			 |	<-------
					|STATE_YELLOW|
		 -------->	|			 |	>---------------------------
		|			 ------------								|
		trans_BY											trans_YG
		|	  ------------------		 ----------------		|
		 --< |  STATE_BLINKING  |		|  STATE_GREEN   | <----
		|	  ------------------		 ----------------	
		|				   ^  ^						|
		|				   |  |						|
		-trans_BB(blinking)-   ---------trans_GB ---

*/


static volatile unsigned tic_counter = 0;
static volatile bool tic_counter_changed_flag = false;
static volatile unsigned blinking_counter = 0;

// create States /////////////////////////////////////////////////////////
#define state_R_name	""	//RED
#define state_Y_name	""	//YELLOW
#define state_G_name	""	//GREEN
#define state_B_name	""	//BLINKING

void stateR_in()	{ PIN_SET_HIGH(LED_RED);     }
void stateR_out()	{ }
void stateY_in()	{ PIN_SET_HIGH(LED_YELLOW);  }
void stateY_out()	{ PIN_SET_LOW(LED_YELLOW); PIN_SET_LOW(LED_RED);   }
void stateG_in()	{ PIN_SET_HIGH(LED_GREEN);   }
void stateG_out()	{ PIN_SET_LOW(LED_GREEN);    }
void stateB_in()	{ }
void stateB_out()	{ PIN_SET_TOGGLE(LED_GREEN); }

State state_R(stateR_in, stateR_out);
State state_Y(stateY_in, stateY_out);
State state_G(stateG_in, stateG_out);
State state_B(stateB_in, stateB_out);

// create Transaction ////////////////////////////////////////////////////
#define trans_RY_name	""
#define trans_YG_name	""
#define trans_GB_name	""
#define trans_BB_name	""	//BLINKING
#define trans_BY_name	""
#define trans_YR_name	""

bool condition_RY() { return TMR1_TimeOUT(RED_PERIOD_msec); }
bool condition_YG() { return TMR1_TimeOUT(YLW_PERIOD_msec) && (blinking_counter==0); }
bool condition_YR() { return TMR1_TimeOUT(YLW_PERIOD_msec) && (blinking_counter!=0); }
bool condition_GB() { return TMR1_TimeOUT(GRN_PERIOD_msec); }
bool condition_BB() { return (++blinking_counter < BLINKING_MAX*2);  }
bool condition_BY() { return (++blinking_counter >= BLINKING_MAX*2); }

void action_trans___() { tic_counter=0; }
void action_trans_YR() { tic_counter=0; blinking_counter=0; }

Transaction trans_RY(condition_RY, action_trans___);
Transaction trans_YG(condition_YG, action_trans___);
Transaction trans_GB(condition_GB, action_trans___);
Transaction trans_BB(condition_BB, action_trans___);
Transaction trans_BY(condition_BY, action_trans___);
Transaction trans_YR(condition_YR, action_trans_YR);

// create Connections ////////////////////////////////////////////////////
Connection conn_RY(&trans_RY, &state_Y);
Connection conn_YG(&trans_YG, &state_G);
Connection conn_GB(&trans_GB, &state_B);
Connection conn_BB(&trans_BB, &state_B);
Connection conn_BY(&trans_BY, &state_Y);
Connection conn_YR(&trans_YR, &state_R);

// in a strict sequence (в строгой очередности)
Connection* p_connections_fromR[] = { &conn_RY};
Connection* p_connections_fromY[] = { &conn_YG, &conn_YR};
Connection* p_connections_fromG[] = { &conn_GB };
Connection* p_connections_fromB[] = { &conn_BB, &conn_BY};

// create StateMachine.......... /////////////////////////////////////////
StateMachine stm;



