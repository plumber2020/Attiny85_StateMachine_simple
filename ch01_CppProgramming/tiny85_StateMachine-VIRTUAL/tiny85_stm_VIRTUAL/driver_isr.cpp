/*
 * driver_isr.cpp
 *
 * Created: 29.01.2023 3:37:08
 *  Author: abram
 */ 

#include "compiler.h"
#include "driver_init.h"
#include <avr/interrupt.h>


ISR(TIM1_COMPA_vect) {
	TMR1_Interrupt(); 
}
