/*
 * driver_init.cpp
 *
 * Created: 29.01.2023 3:41:13
 *  Author: abram
 */ 

#include "driver_init.h"

void GPIO_initialization()
{
	PIN_OUTPUT_DIRECTION(LED_TIC_COUNTER);
	PIN_OUTPUT_DIRECTION(LED_RED);
	PIN_OUTPUT_DIRECTION(LED_YELLOW);
	PIN_OUTPUT_DIRECTION(LED_GREEN);
}

void TIMER_1_initialization()
{
	TMR1_Init();	
}


void system_init()
{
	GPIO_initialization();
	TIMER_1_initialization();

}