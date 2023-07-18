#include "utils/led-bar.h"

#define LED_BAR_FIRST_PIN 0
#define LED_BAR_NLEDS 8

#ifdef __AVR
#include "avrhal/pin.h"
#include "avrhal/time.h"
#define halSetup() ledBarSetup(LED_BAR_NLEDS, LED_BAR_FIRST_PIN)
#else
#include <wiringPi.h>
#define halSetup() wiringPiSetup()
#endif

#include <stdint.h>
#include <stdlib.h>

int main(void)
{
    halSetup();

    ledBarSetup(LED_BAR_NLEDS, LED_BAR_FIRST_PIN);

    uint16_t cycleTime = 2000; // 2000 milliSec	are 0.5 Hz (Instruction-Requirement)
    uint16_t numberOfRuns = 255; // max interpolating range: 0-255
    uint16_t stepTime = (uint16_t)(cycleTime / numberOfRuns);

    while (1) {
        for (uint8_t i = 0; i <= numberOfRuns; i++) {
            ledBarSet(i);
            delay(stepTime);
        }
    }
    return 0;
}
