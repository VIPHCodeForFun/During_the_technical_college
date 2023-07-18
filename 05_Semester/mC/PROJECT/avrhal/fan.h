/*
 * fan.h
 *
 * Created: 25.11.2022 21:17:44
 *  Author: Matthias Gruber, Philipp Vidmar
 */

#include "avrhal/pin.h"
#include "avrhal/pulse-counter.h"

/** Calls setups for PWM + Pulsecounter and sets PIN 31 (Port D - Pin 7) as PWM Pin 
 * 
 */
void fanSetup();

/** Sets Fanspeed on the supported Pin to 0 - 255 -> 0 - 100%
 * @param pin PWM Pin (mostly Pin 31)
 * @param speed Value between 0 - 255
 */
void setFanSpeed(uint8_t pin, uint8_t speed);

/** Gets the current Fanspeed
 * @return Fanspeed in Rpm (revolutions per minute)
 */
uint32_t getFanSpeed();
