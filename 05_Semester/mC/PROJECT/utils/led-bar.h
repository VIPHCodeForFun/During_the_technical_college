/**
 * @author MIC Lab Team
 * @brief LED Bar Control
 */

#ifndef ledbar_h_quws1CohQu22nei2
#define ledbar_h_quws1CohQu22nei2

#include <stdint.h>

/* store the values of "ledBarSetup(uint8_t nLed, uint8_t firstPin)" */
uint8_t N_LEDS;
uint8_t FIRST_PIN;

/** Setup the LED Bar
 *
 * All pins beginning with \p firstPin until \p firstPin + \p nLed -1
 * (including) are configured as outputs.
 * @param[in] nLed Number of LEDs
 * @param[in] firstPin The first pin to be used as LED output
 */
void ledBarSetup(uint8_t nLed, uint8_t firstPin);

/** Set a value for the LED Bar
 *
 * With value 0 all LEDs are turned off. With value 255 all LEDs are turned on.
 * Between that, the number of lit LEDs is interpolated linearly.
 *
 * @param[in] value Value between 0-255 to control the LED pattern
 */
void ledBarSet(uint8_t value);

#endif
