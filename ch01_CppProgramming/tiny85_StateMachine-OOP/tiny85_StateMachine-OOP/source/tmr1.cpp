#include "tmr1.h"
#include <avr/interrupt.h>

// INTERRUPT /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

ISR(TIM1_COMPA_vect) { TMR1_Interrupt(); }


// INIT	//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void TMR1_Initialize() 
{	
	TMR1_CTC_MODE(ENABLE);
	OCR1C = OCR1C_PRESET_VALUE;
	
	TMR1_PWM1A_MODE(DISABLE);
	TMR1_PWM1B_MODE(DISABLE);
	
	TMR1_OC1A_DISCONNECT();
	TMR1_OC1B_DISCONNECT();

	TMR1_INTERRUPT_OCIE1A(ENABLE);
	OCR1A = OCR1A_PRESET_VALUE;
}

void TMR1_START() {
	TMR1_START_PRESCALER(0xF);
}

