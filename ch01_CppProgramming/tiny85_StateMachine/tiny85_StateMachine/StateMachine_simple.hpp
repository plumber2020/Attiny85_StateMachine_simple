#include "StateMachine_simple.h"
#include "stateMachine/StateMachine.h"
#include "source/tmr1.h"
#include "source/pin_manager.h"


#define RED_PERIOD_msec				10000		//RED light
#define YLW_PERIOD_msec				1000		//YLW light
#define GRN_PERIOD_msec				8000		//GREEN light
#define GRN_BLINKING_PERIOD_msec	4000		//GREEN_BLINKING light
#define BLINKING_MAX				5


/*
					 -----------
		 -------->	| STATE_RED |	>-------
		|			 -----------			|
		trans_YR							trans_RY
		|			 ------------			|
		 --------<	|			 |	<-------
					|STATE_YELLOW|
		 -------->	|			 |	>-----------------------
		|			 ------------							|
		trans_BY											trans_YG
		|	  ------------------		 ----------------		|
		 --< |  STATE_BLINKING  |		|  STATE_GREEN   | <----
		|	  ------------------		 ----------------	
		|				   ^  ^						|
		|				   |  |						|
		-trans_BB(blinking)-   ---------trans_BB ---

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

State state_R(state_R_name, stateR_in, stateR_out);
State state_Y(state_Y_name, stateY_in, stateY_out);
State state_G(state_G_name, stateG_in, stateG_out);
State state_B(state_B_name, stateB_in, stateB_out);

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

Transaction trans_RY(trans_RY_name, condition_RY, action_trans___);
Transaction trans_YG(trans_YG_name, condition_YG, action_trans___);
Transaction trans_GB(trans_GB_name, condition_GB, action_trans___);
Transaction trans_BB(trans_BB_name, condition_BB, action_trans___);
Transaction trans_BY(trans_BY_name, condition_BY, action_trans___);
Transaction trans_YR(trans_YR_name, condition_YR, action_trans_YR);

// create Connections ////////////////////////////////////////////////////
Connection conn_RY(&state_R, &trans_RY, &state_Y);
Connection conn_YG(&state_Y, &trans_YG, &state_G);
Connection conn_GB(&state_G, &trans_GB, &state_B);
Connection conn_BB(&state_B, &trans_BB, &state_B);
Connection conn_BY(&state_B, &trans_BY, &state_Y);
Connection conn_YR(&state_Y, &trans_YR, &state_R);

// create StateMachine.......... /////////////////////////////////////////
Connection* p_conn[] = { &conn_RY, &conn_YG, &conn_GB, &conn_BB, &conn_BY, &conn_YR};
StateMachine stm(Connection::count);



