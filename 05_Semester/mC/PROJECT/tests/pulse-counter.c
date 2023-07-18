#include "avrhal/pulse-counter.h"
#include "avrhal/pin.h"
#include "avrhal/time.h"
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "utils/bit.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_NONZERO_VALUE 42
#define PULSE_DURATION_US 10
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

/** Helper function: Generate a pulse on pin PA2 of duration \var PULSE_DURATION_US
*/
void generatePulse()
{
    DDRA |= (1 << PA2);
    PORTA |= (1 << PA2);
    _delay_us(PULSE_DURATION_US);
    PORTA &= ~
	(1 << PA2);
}

/** By invoking the setup function of the pulse-counter module 
 * all required I/O pins should be configured, 
 * 
 * __Expected result:__ Once executed, pin PD2 is configured as input pin,
 * no matter how it was configured before.
*/
bool testPulseCounterSetupIO()
{
    /* Configure as output */
    DDRD |= (1 << PD2);
    /* TODO: Invoke the setup function of the pulse-counter module: */
	pulseCounterSetup();
    /* Now PD2 must be input: */
    return ((DDRD & (1 << PD2)) == 0);
}

/** With no pulse occurring, the values obtained via the result function must be zero.
 * 
 * __Expected result:__  Both, the number of occurred pulses AND the elapsed time are zero.
*/
bool testPulseCounterResultZeroPulse()
{
    uint32_t nPulse = INITIAL_NONZERO_VALUE;
    uint32_t timeFirstToLastPulse = INITIAL_NONZERO_VALUE;

    /* TODO: Invoke the result function of the pulse-counter module
      and store the resulting values in nPulse and timeFirstToLastPulse */
	pulseCounterResult(&nPulse,&timeFirstToLastPulse);
	
    return (nPulse == 0) && (timeFirstToLastPulse == 0);
}

/** With just a single pulse occurring, the elapsed time cannot be calculated and is remaining zero.
 *
 * __Expected result:__  The elapsed time remains zero, pulse count changes to one
*/
bool testPulseCounterResultSinglePulse()
{
    uint32_t nPulse = INITIAL_NONZERO_VALUE;
    uint32_t timeFirstToLastPulse = INITIAL_NONZERO_VALUE;

    generatePulse();
    _delay_ms(2);

    /* TODO: Invoke the result function of the pulse-counter module
      and store the resulting values in nPulse and timeFirstToLastPulse */
	pulseCounterResult(&nPulse,&timeFirstToLastPulse);

    return (nPulse == 1) && (timeFirstToLastPulse == 0);
}

/** With two pulses occurring, the actual elapsed time value can be checked.
 *
 * __Expected result:__ A pulse count of two and an elapsed time
 *  of \var expectedDurationMicros +/- \var maxDeviationMicros.
 **/
bool testPulseCounterResultDuration()
{
    const uint32_t pulseGapMillis = 20;
    __attribute__((unused)) const uint32_t expectedDurationMicros = 1000 * pulseGapMillis + PULSE_DURATION_US;
    __attribute__((unused)) const uint32_t maxDeviationMicros = 700;

    __attribute__((unused)) uint32_t nPulse = 0;
    __attribute__((unused)) uint32_t timeFirstToLastPulse = 0;

    /*Generate two pulses with the specified gap inbetween */
    _delay_ms(200);
    generatePulse();
    _delay_ms(pulseGapMillis);
    generatePulse();
    _delay_ms(200);

    /* TODO: Invoke the result function of the pulse-counter module
      and store the resulting values in nPulse and timeFirstToLastPulse */
	pulseCounterResult(&nPulse,&timeFirstToLastPulse);
    /* TODO: Check whether the actual result matches the expected values and return accordingly. */
	if(nPulse == 2)
		if(timeFirstToLastPulse > (expectedDurationMicros - maxDeviationMicros))
			if(timeFirstToLastPulse < (expectedDurationMicros + maxDeviationMicros)) return true;
	
	
    return false;
	
}

/** The result cannot be queried twice, once it has been queried, the internal state is being reset.
 *
 * __Expected result:__ Once queried by the result function, the internal values are reset to zero.
 * Invoking the result function again - both, the returned number of occurred pulses AND the elapsed time are zero.
 **/
bool testPulseCounterResultReset()
{
    uint32_t nPulse = INITIAL_NONZERO_VALUE;
    uint32_t timeFirstToLastPulse = INITIAL_NONZERO_VALUE;

    /* Call the previous testcase */
    testPulseCounterResultDuration();

    /* TODO: Invoke the result function of the pulse-counter module one more time,
      and store the resulting values in nPulse and timeFirstToLastPulse */
	pulseCounterResult(&nPulse,&timeFirstToLastPulse);
    return (nPulse == 0) && (timeFirstToLastPulse == 0);
}

/** Invoking setup should reset the internal state of the pulse-coounter module.
 * 
 * __Expected result:__ Running the setup function, the internal values are supposed to be reset.
 * Invoking the result function afterwards - both - the returned number of occurred pulses AND the elapsed time are zero.
 **/
bool testPulseCounterResetBySetup()
{
    uint32_t nPulse = 0;
    uint32_t timeFirstToLastPulse = 0;

    _delay_ms(200);
    generatePulse();
    _delay_ms(20);
    generatePulse();
    _delay_ms(200);

    /* TODO: Invoke pulse-counter module setup again. */
	pulseCounterSetup();
    /* TODO: Invoke the result function of the pulse-counter module
      and store the resulting values in nPulse and timeFirstToLastPulse */
	pulseCounterResult(&nPulse,&timeFirstToLastPulse);
    return (nPulse == 0) && (timeFirstToLastPulse == 0);
}

void testSetup()
{
    /* TODO: Initialize all required avrhal modules here.
      Ideally you only need to run the setup function of the pulse-counter module,
      it should handle every thing else internally (like invoking timeSetup() etc.) */
	pulseCounterSetup();
}

/** Run all specified tests
 * 
*/
void runTests()
{
    typedef bool (*TestFunction)(void);

    const char* testNames[] = {
        "testPulseCounterSetup", "testPulseCounterZeroPulse",
        "testPulseCounterSinglePulse", "testPulseCounterDurationResult",
        "testPulseCounterReset", "testPulseCounterResetBySetup"
    };
    TestFunction tests[] = {
        testPulseCounterSetupIO, testPulseCounterResultZeroPulse,
        testPulseCounterResultSinglePulse, testPulseCounterResultDuration,
        testPulseCounterResultReset, testPulseCounterResetBySetup
    };

    for (uint8_t i = 0; i < ARRAY_SIZE(tests); ++i) {
        testSetup();

        /* Run the test */
        const bool success = tests[i]();

        usartStringPrintln("%s : %s ", testNames[i], success ? "pass" : "fail");
    }
}

void printTestNotice()
{
    usartStringPrintln("===[ pulse-counter Test ]=============================");
    usartStringPrintln("Connect Pins PA2 <-> PD2 before running this test.");
    _delay_ms(330);
    usartStringPrintln("======================================================");
    _delay_ms(330);
}

int main()
{
    usartSetup(USART_B9600, USART_CONFIG_8N1);
    sei();

    while (1) {
        printTestNotice();
        runTests();
        _delay_ms(250.0);
    }

    return 0;
}

