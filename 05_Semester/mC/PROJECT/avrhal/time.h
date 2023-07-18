/**
 * @author MIC Lab Team
 * @brief System time and delay
 *
 */

#include "utils/bit.h"
#include <util/atomic.h>
#include <avr/interrupt.h>

#ifndef time_h_EiPhopws3itohn22
#define time_h_EiPhopws3itohn22

#include <util/delay.h>
#define MILLISECOND 1
#include <stdint.h>

/** Setup hardware timer 0 as system time
 *
 */
void timeSetup();

/** Elapsed time since power on
 *
 * Time granularity: 8 microseconds
 * @note Elapsed time since invocation of timeSetup() and sei()
 * @note Overflow-Calculation:
 * 2^32 = Overflow at 4294967296us -> /10^6 = 4294.97 sec -> /60 = 71,58min
 * @return elapsed time in microseconds
 */
uint32_t micros();

/** Elapsed time since power on
 *
 * Time granularity: 1 millisecond
 * @note Elapsed time since invocation of timeSetup() and sei()
 * @note Overflow-Calculation: 
 * 2^32 = Overflow at 4294967296ms -> /(1000 * 60 * 60 * 24) = 49.710 Days
 * @return elapsed time in milliseconds
 */
uint32_t millis();

/** Busy-wait for the given amount of milliseconds
 *
 * @param[in] milliSeconds the amount of milliseconds to wait.
 */
void delay(uint16_t milliSeconds);


/** Sets a new start-time instead of time since power on. 
 *
 * 
 */
void setStartTime();


/** Set PD7 to fast PWM
*/
void setupPWM();

#endif
