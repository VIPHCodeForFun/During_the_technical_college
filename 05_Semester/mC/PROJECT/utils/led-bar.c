#include "led-bar.h"

#ifdef __AVR
#include "avrhal/pin.h"
#else
#include <wiringPi.h>
#endif
#include <stdlib.h>

void ledBarSetup(uint8_t nLed, uint8_t firstPin)
{
    N_LEDS = nLed;
    FIRST_PIN = firstPin;
    for (uint8_t i = firstPin; i < firstPin + nLed; i++) {
        pinMode(i, OUTPUT);
    }
}

void ledBarSet(uint8_t value)
{

    uint8_t maxValue = 255;

    /* Error handling */
    if (value > maxValue) {
        return;
    }

    // Turns on the LEDS in the correct range
    uint8_t step = (uint8_t)(maxValue / (N_LEDS + 1)); //! (N-LEDs+1)= divides the area into the desired subareas (0 LEDS on is also an area)
    uint8_t ledOn = FIRST_PIN;

    for (uint16_t i = step; i < value; i += step) {
        if (ledOn < FIRST_PIN + N_LEDS) {
            digitalWrite(ledOn, HIGH);
            ledOn++;
        }
    }

    // Turns off the LEDS that are not required
    uint8_t ledOff = ledOn++;

    for (uint8_t i = ledOff; i < FIRST_PIN + N_LEDS; i++) {
        digitalWrite(i, LOW);
    }
}
