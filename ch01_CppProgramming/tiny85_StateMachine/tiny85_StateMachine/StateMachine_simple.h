#pragma once

#define TMR1_INTERRUPT_FREQ		2	//Hz

#define RED_PERIOD_sec			10		//RED light
#define YLW_PERIOD_sec			1		//RED&YLW light
#define GRN_PERIOD_sec			8		//GREEN light
#define GRN_BLINKING_PERIOD_sec	4		//GREEN_BLINKING light
#define BLINKING_MAX			5


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

void StateMachine_Initialize();
void StateMachine_eventCHECKING();
