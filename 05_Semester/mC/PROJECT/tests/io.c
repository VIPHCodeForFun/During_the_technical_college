#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>

#include "avrhal/pin.h"

/** Test for connection between two pins, each one of Port B and Port D.
 *
 * Named raw, as it uses direct register access for all I/O.
 * Useful for ensuring proper physical connection before testing the HAL functions pinMode(), digtalWrite() etc.
 *
 * @return Number of passed tests (All passed == 4)
*/
uint8_t testConnectionRaw(const uint8_t pinPortB, const uint8_t pinPortD)
{
    DDRB = 1 << pinPortB; // Output
    DDRD = 0x00; // Input
    PORTD = 0x00; // No pullup

    PORTB = (1 << pinPortB); // Set output high
    _delay_ms(1);
    uint8_t nTestsPassed = 0;
    if ((PIND & (1 << pinPortD)) != 0) { // Check read high
        nTestsPassed += 1;
    } else {
        return nTestsPassed;
    }
    PORTB &= ~(1 << pinPortB); // Set output low
    _delay_ms(1);
    if ((PIND & (1 << pinPortD)) == 0) { // Check read low
        nTestsPassed += 1;
    } else {
        return nTestsPassed;
    }

    // Swap direction

    DDRD = 1 << pinPortD; // Output
    DDRB = 0x00; // Input
    PORTB = 0x00; // No pullup

    PORTD |= (1 << pinPortD); // Set output high
    _delay_ms(1);
    if ((PINB & (1 << pinPortB)) != 0) { // Check read high
        nTestsPassed += 1;
    } else {
        return nTestsPassed;
    }
    PORTD &= ~(1 << pinPortD); // Set output low
    _delay_ms(1);
    if ((PINB & (1 << pinPortB)) == 0) { // Check read low
        nTestsPassed += 1;
    }

    return nTestsPassed;
}

/** Test whether 2 given pins are connected.
 *
 * One pin is configured as output, while the other pin is left as an input.
 * When toggling the output pin, the signal level observed at the input pin should change accordingly.
 *
 * @param pinA The output pin
 * @param pinB The input pin
 *
 * @return Number of passed tests (All passed == 2)
*/
uint8_t testConnection(const uint8_t pinA, const uint8_t pinB)
{
    uint8_t nTestsPassed = 0;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, INPUT);

    digitalWrite(pinA, HIGH);
    _delay_ms(1);

    if (digitalRead(pinB) == HIGH) {
        nTestsPassed += 1;
    } else {
        pinMode(pinA, INPUT); // Reset pin to input mode on exit
        return nTestsPassed;
    }

    digitalWrite(pinA, LOW);
    _delay_ms(1);

    if (digitalRead(pinB) == LOW) {
        nTestsPassed += 1;
    }
    pinMode(pinA, INPUT); // Reset pin to input mode on exit
    return nTestsPassed;
}

/** Test whether the internal pullup works as expected for 2 connected pins.
 *
 * The first pin is configured as output and set LOW (= sinking current).
 * The second pin is configured as input with pullup enabled.
 * Regardless we should read LOW on the second pin (as the output pin is able to sink way more current than the path via the pullup can provide).
 * When reconfiguring the output as input (= high impedance), the signal level observed on the second pin finally should raise to HIGH, due to the internal pullup.
 *
 * @param pinA The output pin
 * @param pinB The input pin
 *
 * @return Number of passed tests (All passed == 2)
*/
uint8_t testInternalPullup(const uint8_t pinA, const uint8_t pinB)
{
    uint8_t nTestsPassed = 0;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, INPUT);
    pullUpDnControl(pinB, PUD_UP);

    digitalWrite(pinA, LOW);
    _delay_ms(1);
    if (digitalRead(pinB) == LOW) {
        nTestsPassed += 1;
    } else {
        pinMode(pinA, INPUT);
        pullUpDnControl(pinB, PUD_OFF);
        return nTestsPassed;
    }

    pinMode(pinA, INPUT);
    _delay_ms(1);
    if (digitalRead(pinB) == HIGH) {
        nTestsPassed += 1;
    }

    pullUpDnControl(pinB, PUD_OFF);
    pinMode(pinA, INPUT); // Reset pin to input mode on exit
    return nTestsPassed;
}

/** Test whether we attempt to set the pullup for pins which are configured as output (which should not happen :-) )
 *
 * @param pinA The output pin
 * @param pinB The input pin
 */
uint8_t testAddPullupWithOutput(const uint8_t pinA, const uint8_t pinB)
{
    uint8_t nTestsPassed = 0;

    pinMode(pinA, OUTPUT);
    pinMode(pinB, INPUT);

    digitalWrite(pinA, LOW);

    pullUpDnControl(pinA, PUD_UP);
    _delay_ms(1);
    if (digitalRead(pinB) == LOW) {
        nTestsPassed += 1;
    }
    return nTestsPassed;
}

void visualizeSuccess()
{
    for (int i = 0; i < 40; ++i) {
        PORTA = (1 << (i & 3)) + (0x80 >> (i & 3));
        if (i < 25) {
            _delay_ms(50);
        }
        _delay_ms(50);
    }
    PORTA = 0;
}

const uint8_t offsetPortB = 8;
const uint8_t offsetPortD = 3 * 8;
const uint8_t firstPin = 4;
const uint8_t nPinPerPort = 4;
const uint8_t nTestsPerConnection = 4;

uint8_t testConnectionsRaw()
{
    uint8_t nTestsPassed = 0;

    for (uint8_t i = 0; i < nPinPerPort; ++i) {
        const uint8_t nTestsPassedPrev = nTestsPassed;
        nTestsPassed += testConnectionRaw(firstPin + i, firstPin + i);
        if (nTestsPassed - nTestsPassedPrev != nTestsPerConnection) {
            break;
        }
    }

    return nTestsPassed;
}

uint8_t testConnections()
{
    uint8_t nTestsPassed = 0;

    for (uint8_t i = 0; i < nPinPerPort; ++i) {
        const uint8_t pinPortB = offsetPortB + firstPin + i;
        const uint8_t pinPortD = offsetPortD + firstPin + i;

        uint8_t nTestsPassedPrev = nTestsPassed;
        nTestsPassed += testConnection(pinPortB, pinPortD);
        if (nTestsPassed - nTestsPassedPrev != nTestsPerConnection / 2) {
            break;
        }
        nTestsPassedPrev = nTestsPassed;
        nTestsPassed += testConnection(pinPortD, pinPortB);
        if (nTestsPassed - nTestsPassedPrev != nTestsPerConnection / 2) {
            break;
        }
    }
    return nTestsPassed;
}

uint8_t testInternalPullups()
{
    uint8_t nTestsPassed = 0;

    for (uint8_t i = 0; i < nPinPerPort; ++i) {
        const uint8_t pinPortB = offsetPortB + firstPin + i;
        const uint8_t pinPortD = offsetPortD + firstPin + i;

        uint8_t nTestsPassedPrev = nTestsPassed;
        nTestsPassed += testInternalPullup(pinPortB, pinPortD);
        if (nTestsPassed - nTestsPassedPrev != nTestsPerConnection / 2) {
            break;
        }
        nTestsPassedPrev = nTestsPassed;
        nTestsPassed += testInternalPullup(pinPortD, pinPortB);
        if (nTestsPassed - nTestsPassedPrev != nTestsPerConnection / 2) {
            break;
        }
    }
    return nTestsPassed;
}

int main()
{
    DDRA = 0xFF;
    PORTA = 0x00;

    uint8_t nTestsPassed = 0;

    while (1) {
        _delay_ms(250.0);

        nTestsPassed = testConnectionsRaw();

        const uint8_t allPassed = nPinPerPort * nTestsPerConnection;

        if (nTestsPassed != allPassed) {
            // Last test failed - display the number of passed tests :/
            PORTA = nTestsPassed;
            // NOTE: Please check the physical connections (jumper wires) between the pins
            continue;
        }

        nTestsPassed += testConnections();
        if (nTestsPassed != 2 * allPassed) {
            // Last test failed - display the number of passed tests :/
            PORTA = nTestsPassed;
            // Probably an issue in the avrhal layer
            continue;
        }

        nTestsPassed += testInternalPullups();
        if (nTestsPassed != 3 * allPassed) {
            // Last test failed - display the number of passed tests :/
            PORTA = nTestsPassed;
            // Probably an issue in the avrhal layer with pullUpDnControl();
            continue;
        }

        const uint8_t finalTestPassed = 1;
        nTestsPassed += testAddPullupWithOutput(offsetPortB + firstPin, offsetPortD + firstPin);

        if (nTestsPassed == (3 * allPassed + finalTestPassed)) {
            visualizeSuccess();
        } else {
            PORTA = nTestsPassed;
            // Probably an issue in the avrhal layer with pullUpDnControl():
            // pullUpDnControl() should only have an effect when the given pin
            // is in input mode.
        }
    }

    return 0;
}
