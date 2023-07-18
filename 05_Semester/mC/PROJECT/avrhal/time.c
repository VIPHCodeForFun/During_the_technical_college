#include "time.h"
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"

volatile uint32_t timecounter;

static inline void enableTimerInterrupt()
{
	// for ComparMatch
	BIT_SET(TIMSK, OCIE0); // Datasheet ATmega32 p.82
}

static inline void disableTimerInterrupt()
{
	// for CompareMatch
	BIT_CLR(TIMSK, OCIE0); // Datasheet ATmega32 p.82
}

void timeSetup()
{
	// Set CTC-Mode
	BIT_SET(TCCR0, WGM01); // Datasheet ATmega32 p.80
	BIT_CLR(TCCR0, WGM00); // Datasheet ATmega32 p.80

	/* Calculation prescaler */
	// 8 000 000 Hz = 0,125 ms
	// 2048us / 256 = 8 us
	// 8us / 0,125ms = 64
	BIT_SET(TCCR0, CS00); // Datasheet ATmega32 p.82
	BIT_SET(TCCR0, CS01); // Datasheet ATmega32 p.82
	BIT_CLR(TCCR0, CS02); // Datasheet ATmega32 p.82

	// Compare Value = 2000us / 8 = 250 (We use 249, because 0 is also a value)
	OCR0 = 249; // Datasheet ATmega32 p.82

	enableTimerInterrupt();
}

uint32_t micros()
{
	uint32_t currentTimerCounter = 0;
	uint32_t currentTimerValue = 0;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		currentTimerCounter = timecounter;
		currentTimerValue = TCNT0; // Datasheet ATmega32 p.82
	}
	// * 1000 --> MilliSekonds to microSekonds
	// * 2	  --> timecounter 1 = 2 milliSekonds
	currentTimerCounter = currentTimerCounter * 1000 * 2;
	// * 8	  --> 1 Value = 8 microsekonds
	currentTimerValue = currentTimerValue * 8;

	return currentTimerCounter + currentTimerValue;
}

uint32_t millis()
{
	uint32_t currentTimerCounter = 0;
	uint8_t currentTimerVallue = 0;
	uint8_t halfOCR0 = floor(OCR0 / 2);

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		currentTimerCounter = timecounter;
		currentTimerVallue = TCNT0;
	}

	if (currentTimerVallue < halfOCR0) {
		// * 2 --> timecounter 1 = 2 milliSekonds
		return (currentTimerCounter * 2);
	}
	// * 2 --> timecounter 1 = 2 milliSekonds
	// + 1 --> 1 milliSekond
	return (currentTimerCounter * 2) + 1;
}

void delay(uint16_t milliSeconds)
{
	for (uint16_t i = 0; i < milliSeconds; i++) {
		_delay_ms(MILLISECOND);
	}
}

void setStartTime()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		timecounter = 0;
	}
}

/* ---------------------------------------------------- */

ISR(TIMER0_COMP_vect)
{
	timecounter++;
}
