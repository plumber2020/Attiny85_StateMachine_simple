#ifndef TMR1_H_
#define TMR1_H_

#include "device_config.h"
#include "pin_manager.h"

#define TMR1_BOTTOM				0
#define TMR1_MAX				255


// INIT ///////////////////////////////////////////////////////////////////

#define	TMR1_INTERRUPT_OCIE1A(BIT)		TIMSK  |= (BIT<<OCIE1A)
#define	TMR1_INTERRUPT_OCIE1B(BIT)		TIMSK  |= (BIT<<OCIE1B)
#define	TMR1_INTERRUPT_OVFL1(BIT)		TIMSK  |= (BIT<<TOIE1)

void TMR1_Interrupt();


//////////////////////////////////////////////////////////////////////////

/*
	Divider =	1	(8M/1    ) ==>	Fin=   8000k		(/256) ==>	Fout=31250		Hz
				2	(8M/2    ) ==>	Fin=   4000k		(/256) ==>	Fout=15625.0	Hz
				4	(8M/4    ) ==>	Fin=   2000k		(/256) ==>	Fout=78120.5	Hz	
				8	(8M/8    ) ==>	Fin=   1000k		(/256) ==>	Fout=3906.25	Hz
				16	(8M/16   ) ==>	Fin=    500k		(/256) ==>	Fout=1953.125	Hz
				32	(8M/32   ) ==>	Fin=    250k		(/256) ==>	Fout=976.5625	Hz
				64	(8M/64   ) ==>	Fin=    125k		(/256) ==>	Fout=488.28125	Hz
				128	(8M/128  ) ==>	Fin=     62k5	 	(/256) ==>	Fout=244,14		Hz
				256	(8M/256  ) ==>	Fin=     31k25		(/256) ==>	Fout=122.07		Hz
				512	(8M/512  ) ==>	Fin=  15625.0		(/256) ==>	Fout= 61.03		Hz
				1024(8M/1024 ) ==>	Fin=  78120.5		(/256) ==>	Fout= 30.52		Hz
				2048(8M/2048 ) ==>	Fin=   3906.25		(/256) ==>	Fout= 15.26		Hz
				4096(8M/4096 ) ==>	Fin=   1953.125		(/256) ==>	Fout=  7.63		Hz	
				8192(8M/8192 ) ==>	Fin=	976.5625	(/256) ==>	Fout=  3.81		Hz	
			   16384(8M/16384) ==>	Fin=	488.28125	(/256) ==>	Fout=  1.91		Hz	

*/

#define	TMR1_DIVIDER						16384UL
#define	TMR1_START_PRESCALER(PRESCALER)		TCCR1 |= ((PRESCALER&0xF)<<CS10)

#define	OCR1C_PRESET_VALUE			244		// Fin=	488.28125Hz; OCR1C = Fin/Fout = 488Hz/2Hz = 244
#define	OCR1A_PRESET_VALUE			200		// any value less OCR1C
#define TMR1_INTERRUPT_PERIOD_ms	OCR1C_PRESET_VALUE*TMR1_DIVIDER/(F_CPU/1000)	//499

bool TMR1_TimeOUT(unsigned delay_ms);

/*
	TMR0 Setting MODE
*/

#define	TMR1_CTC_MODE(BIT)			TCCR1 |= (BIT<<CTC1)	// Clear Timer/Counter on Compare Match with OCR1C register value
#define	TMR1_PWM1A_MODE(BIT)		TCCR1 |= (BIT<<PWM1A)	// Pulse Width Modulator A Enable based on comparator OCR1A
#define	TMR1_PWM1B_MODE(BIT)		GTCCR |= (BIT<<PWM1B)	// Pulse Width Modulator A Enable based on comparator OCR1B
								
/*
	TMR0 Setting Output
	OC0A - outputA disconnected
	OC0B - outputB disconnected
*/

#define	TMR1_OC1A_DISCONNECT()			TCCR1 &=~(0b11<<COM1A0)
#define	TMR1_OC1A_CONNECTION(BITS)		TCCR1 |= (BITS<<COM1A0)

#define	TMR1_OC1B_DISCONNECT()			GTCCR &=~(0b11<<COM1B0)
#define	TMR1_OC1B_CONNECTION(BITS)		GTCCR |= (BITS<<COM1B0)


//////////////////////////////////////////////////////////////////////////

void TMR1_Initialize();
void TMR1_START();


#endif /* TMR1_H_ */