/**
 * @author MIC Lab Team
 * @brief Our avrhal core functions
 *
 */

#ifndef pin_h_Aidwsdo1usieG22p
#define pin_h_Aidwsdo1usieG22p

#include <stdbool.h>
#include <stdint.h>

#define HIGH 1
#define LOW 0
#define PINS_PER_REGISTER 8

#define PWM_PIN 31

#define ADC0  0b00000000
#define ADC1  0b00000001
#define ADC2  0b00000010
#define ADC3  0b00000011
#define ADC4  0b00000100
#define ADC5  0b00000101
#define ADC6  0b00000110
#define ADC7  0b00000111

typedef enum { 
	INPUT,
    OUTPUT,
    PWM_OUTPUT 
} Mode;

typedef enum {
    PUD_NOT_SUPPORTED = 0xFF,
    PUD_OFF = 0,
    PUD_DOWN = PUD_NOT_SUPPORTED, // Only available on the raspberry pi
    PUD_UP = 2
} PullUpDown;

/** Set pin mode
 *
 * Setup a pin as input, output or pwm output.
 *
 * @note PWM output is only configurable for pin PD7.
 * When requested, the pin is set up in "Fast PWM Mode" at 31 kHz.
 *
 * @note PWM output is going to be implementated as part of assignment 3&4
 * and not required for assignment 1&2.
 *
 * @param[in] pin avrhal pin number
 * @param[in] mode requested pin mode (INPUT, OUTPUT or PWM_OUTPUT)
 *
 */
void pinMode(uint8_t pin, Mode mode);

/** Set pin output state (HIGH or LOW)
 *
 * Without effect when invoked for an input pin.
 *
 * @param[in] pin avrhal pin number
 * @param[in] value requested pin state (HIGH or LOW)
 */
void digitalWrite(uint8_t pin, uint8_t value);

/** Read a pin value
 *
 * May be performed in any 'Mode' (INPUT, OUTPUT, PWM_OUTPUT).
 *
 * @param[in] pin avrhal pin number
 *
 * @return pin state (HIGH or LOW)
 */
uint8_t digitalRead(uint8_t pin);

/** Help function Set up ADC 8 bit 
 *
 */
void adcSetup();

/** Help function ADC correct MUX
 * @param[in] pin avrhal pin number
 *
 */
void setAnalogInputPin (uint8_t pin);

/** Help function ADC busy-waits until the conversion is completed.
 *
 * @return The 8-bit conversion result
 */
uint8_t adcSingleRun();

/** Carry out a single AD Conversion.
 *
 * This call busy-waits until the conversion is completed.
 *
 * @param[in] pin avrhal pin number
 * @note According to the Datasheet (p.204 and p.206) the first Conversion takes 25 Cycles,
 * after that a Conversion takes 13 Cylces. 
 * If we but that into correlation to our ADC-Clock we get: 
 * (1/1250000) * 25 = 200us for the First Conversion
 * (1/1250000) * 13 = 104us for a normal Conversion
 * @return The 10-bit conversion result
 */
uint8_t analogRead(uint8_t pin);

/** Configures the AD Converter as free running for the given pin.
 *
 * @param[in] pin avrhal pin number
 */
void analogReadFreeRunning(uint8_t pin);

/** Obtain last AD result
 *
 * When configured via analogReadFreeRunning() this
 * function may be used to obtain the last reading.
 *
 * The value "-1" is returned when no result is available
 * or the pin was not configured via analogReadFreeRunning().
 *
 * @param[in] pin avrhal pin number
 * @param[in] clear set true to clear the last result
 * @return last conversion result or -1
 */
int16_t analogReadLast(uint8_t pin, bool clear);

/** Input Pull Up Control
 *
 * Invokation is without effect when the given pin is not in input mode.
 * The function name has been adopted from the WiringPi library.
 *
 * @note The ATmega 32 has no internal pulldown resistors.
 * For compatibility reason the "Dn" part is kept in the function name.
 *
 * @param[in] pin avrhal pin number
 * @param[in] pud requested pullup configuration (PUD_OFF or PUD-UP are
 * supported)
 */
void pullUpDnControl(uint8_t pin, PullUpDown pud);

/** Set the PWM Duty cycle
 *
 * @note When using pwmWrite(), first use pinMode() to configure the pin as pwm
 * output.
 *
 * @note pwmWrite() only works for specific pins @see pinMode()
 *
 * @param[in] pin avrhal pin number
 * @param[in] dutyCycle 8-bit duty-cycle value (0-255)
 */
void pwmWrite(uint8_t pin, uint8_t dutyCycle);

/** Get port number for ATMEGA32
 *
 * @note mapps port from <wiringPi.h> to register ATMEGA32
 *
 * @param[in] pin avrhal pin number
 */
unsigned int getPortNumber(uint8_t pin);

/** Get pin number for ATMEGA32
 *
 * @note mapps pin from <wiringPi.h> to register ATMEGA32
 *
 * @param[in] pin avrhal pin number
 */
unsigned int getPinNumber(uint8_t pin);



/** Setup for PWM and timer configuration
 *
 */
void setupPWM();




#endif
