/*
 * pulse_counter.c
 *
 * Created: 17.11.2022 22:04:06
 *  Author: Philipp Vidmar, Matthias Gruber
 */ 

#include "avrhal/pulse-counter.h"

volatile uint32_t pulsecounter;
volatile uint32_t startTimeValue; // microsec; 

void pulseCounterSetup()
{
	timeSetup();
	pulseCounterReset();
	
	// Set the Interrupt to activate on falling edges
	BIT_SET(MCUCR,ISC01); // Datasheet ATmega32 p. 67
	BIT_CLR(MCUCR,ISC00); // Datasheet ATmega32 p. 67
	
	// Enable extern Interrupt
	BIT_SET(GICR,INT0); // Datasheet ATmega32 p. 68
	
	// Set PD2 to Input
	pinMode(26,INPUT); 
		
}

void pulseCounterReset()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
	pulsecounter = 0;
	}
	startTimeValue = micros();
}


void pulseCounterResult(uint32_t* pulses,uint32_t* time)
{
	uint32_t pastTime = micros();
	uint32_t pastTimeValue = pastTime - startTimeValue;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
	*pulses = pulsecounter;
	}
	if(*pulses == 0 || *pulses == 1)
	{
		* time = 0;
	}
	else
	{
		*time = pastTimeValue;
	}
	
	pulseCounterReset();
}

/* ---------------------------------------------------- */

ISR(INT0_vect)
{
	pulsecounter++;
}