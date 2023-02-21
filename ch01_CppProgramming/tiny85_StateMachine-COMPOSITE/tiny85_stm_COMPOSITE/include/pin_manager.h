#ifndef PIN_MANAGER_H_
#define PIN_MANAGER_H_

#include "compiler.h"


#define PIN_INPUT_DIRECTION(PIN)		DDRB  &=~(1<<(PIN))
#define PIN_OUTPUT_DIRECTION(PIN)		DDRB  |= (1<<(PIN))
#define PIN_SET_HIGH(PIN)				PORTB |= (1<<(PIN))
#define PIN_SET_LOW(PIN)				PORTB &=~(1<<(PIN))
#define PIN_SET_TOGGLE(PIN)				PORTB ^= (1<<(PIN))



// STATES ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define LED_TIC_COUNTER					PB0
#define LED_RED							PB1
#define LED_YELLOW						PB2
#define LED_GREEN						PB3
#define LED_SUPER						PB4


#endif /* PIN_MANAGER_H_ */