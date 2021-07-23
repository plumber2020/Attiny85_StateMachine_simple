/*
 * tiny85_StateMachine.cpp
 *
 * Emulale SEMAFOR RYG lighting 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "source/tmr1.h"
#include "StateMachine_simple.h"

/*

	 ---------------------------
	|ATTINY85			PB0		|- LED_TIC_COUNTER		
	|					PB1		|- LED_RED				
	|					PB2		|- LED_YELLOW
	|					PB3		|- LED_GREEN
	|					PB4		|- LED_TIC_RESET
	|					PB5		|- 
	 ---------------------------

*/

void Initialaze() {
	PIN_OUTPUT_DIRECTION(LED_TIC_COUNTER);
	PIN_OUTPUT_DIRECTION(LED_TIC_RESET);
	PIN_OUTPUT_DIRECTION(LED_RED);
	PIN_OUTPUT_DIRECTION(LED_YELLOW);
	PIN_OUTPUT_DIRECTION(LED_GREEN);
	
	TMR1_Initialize();
	TMR1_START();
}


int main(void)
{
	Initialaze();
	StateMachine_Initialize();
	TMR1_START();
	
	sei();
	   
    while (1) 
    {
		StateMachine_eventCHECKING();
    }
}

