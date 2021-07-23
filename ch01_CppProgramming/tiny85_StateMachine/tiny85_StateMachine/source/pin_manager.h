#ifndef PIN_MANAGER_H_
#define PIN_MANAGER_H_

#include <avr/io.h>


#define PIN_INPUT_DIRECTION(PIN)		DDRB  &=~(1<<(PIN))
#define PIN_OUTPUT_DIRECTION(PIN)		DDRB  |= (1<<(PIN))
#define PIN_SET_HIGH(PIN)				PORTB |= (1<<(PIN))
#define PIN_SET_LOW(PIN)				PORTB &=~(1<<(PIN))
#define PIN_SET_TOGGLE(PIN)				PORTB ^= (1<<(PIN))

#define DISABLE							0
#define ENABLE							1

#define LOW								0
#define HIGH							1


// STATES ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define LED_TIC_COUNTER					PB0
#define LED_RED							PB1
#define LED_YELLOW						PB2
#define LED_GREEN						PB3
#define LED_TIC_RESET					PB4


#endif /* PIN_MANAGER_H_ */