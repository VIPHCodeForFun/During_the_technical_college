
#include "avrhal/pin.h"
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "utils/bit.h"

#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

static inline void enableTimerInterrupt()
{
	// enable interrupt on CompareMatch Datasheet p.82
	BIT_SET(TIMSK,OCIE0);
}

static inline void disableTimerInterrupt()
{
	BIT_CLR(TIMSK,OCIE0);
}


volatile uint32_t counter;

ISR(TIMER0_COMP_vect)
{
	counter++;
}


void timerSetup()
{
	// Waveform Generation: CTC-Mode
	BIT_SET(TCCR0,WGM01);  // Datasheet p. 80
	BIT_CLR(TCCR0,WGM00);
	
	
	//***Clock-Calcualtion***//
	// F_CPU = 8000000 Hz
	// CycleTime = 2048 usec
	// Steptime = 2048 / 256 = 8
	
	// 1/F_CPU = 0,125 usec
	// 8 usec / 0,125 usec = 64
	
	// Clock Selection Bits
	BIT_SET(TCCR0,CS00);
	BIT_SET(TCCR0,CS01);
	BIT_CLR(TCCR0,CS02); // Datasheetp. 82
	
	
	//***Overflow-Calculation***//
	// 2048 usec = 256 Steps
	// 2000 / 8 = 250 Steps => 249;
	// Every Step equals two 2 millisecs
	
	// ComapareMatch
	OCR0 = 249;		// Datasheet p.82
	
}

void timerSetupFast()
{
	// for info see timersetup()
	BIT_SET(TCCR0,WGM01); // p. 80
	BIT_CLR(TCCR0,WGM00);
	
	BIT_SET(TCCR0,CS00);
	BIT_SET(TCCR0,CS01);
	BIT_CLR(TCCR0,CS02);
	
	OCR0 = 100;		// p.82
}

void printCounterForever()
{
	timerSetup();
	
	while (1) {
		usartStringPrintln("Value: %lu, (max: %lu)", counter, (uint32_t)-1);
		_delay_ms(200);
	}
}

void printMillisecondsForever()
{
	timerSetup();
	
	while(1)
	{
		uint32_t elepsedTime = (counter * 2);
		usartStringPrintln("Time elapsed: %lu milliseconds", elepsedTime);
		_delay_ms(200);
	}
}

void printBadCounterForever()
{
	timerSetupFast();

	uint32_t lastLastCount = 0;
	uint32_t lastCount = 0;

	while (1) {
		if (lastCount > counter) {
			/* This is an error case, as we always expect that counter >=
			* lastCount, except for an overflow of counter. */
			disableTimerInterrupt();
			const uint32_t counter_ = counter;
			PORTA = 0xFF;
			usartStringPrintln("Result  lastCount:%lu counter_:%lu  (LastLast:%lu Max:%lu)", lastCount, counter_, lastLastCount, (uint32_t)-1);
			_delay_ms(100);
			enableTimerInterrupt();
		}
		lastLastCount = lastCount;
		lastCount = counter;
	}
}

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;
	
	usartSetup(USART_B9600, USART_CONFIG_8N1);

	sei();

	enableTimerInterrupt();

	//printMillisecondsForever();
	//printCounterForever();
	
	// trying out the Exercise from the lab instructions....
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		printBadCounterForever();
	}
	
}
