#include "pin.h"
#include "utils/bit.h"
#include <avr/io.h>

static volatile uint8_t* const DATA_DIRECTION_REGISTERS[] = { &DDRA, &DDRB, &DDRC, &DDRD };
static volatile uint8_t* const PORT_REGISTERS[] = { &PORTA, &PORTB, &PORTC, &PORTD };
static volatile uint8_t* const PIN_REGISTER[] = { &PINA, &PINB, &PINC, &PIND };


void setupPWM()
{
	// Set Pin PD7 as Output
	BIT_SET(*DATA_DIRECTION_REGISTERS[getPortNumber(PWM_PIN)], getPinNumber(PWM_PIN));
	
	// Set 2.timer mode to fast PWM
	BIT_SET(TCCR2,WGM21);	// Datasheet ATmega32 p. 125
	BIT_SET(TCCR2,WGM20);	// Datasheet ATmega32 p. 125
	
	// Clear OC2 on compare match
	BIT_SET(TCCR2,COM21);	// Datasheet ATmega32 p. 126
	BIT_CLR(TCCR2,COM20);	// Datasheet ATmega32 p. 126
	
	// Set prescaler to 256 --> 8MHz /256 = 31.37 kHz
	BIT_SET(TCCR2,CS22);	// Datasheet ATmega32 p. 126
	BIT_SET(TCCR2,CS21);	// Datasheet ATmega32 p. 126
	BIT_CLR(TCCR2,CS20);	// Datasheet ATmega32 p. 126
}

void disconnectOC2()
{
	// Set PWM to not inverted
	BIT_CLR(TCCR2,COM21);	// Datasheet ATmega32 p. 126
	BIT_CLR(TCCR2,COM20);	// Datasheet ATmega32 p. 126
}

void pinMode(uint8_t pin, Mode mode)
{
    if (mode == OUTPUT) {
        if (pin == PWM_PIN)
		{
			disconnectOC2();
		}
		BIT_SET(*DATA_DIRECTION_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
    }
	else if (mode == INPUT) {
        BIT_CLR(*DATA_DIRECTION_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
    }
	else if (mode == PWM_OUTPUT && pin == PWM_PIN) // Only PD7
	{
		setupPWM();
		OCR2 = 0; // Datasheet ATmega32 p. 127
	}
}

void digitalWrite(uint8_t pin, uint8_t value)
{
    if (value == HIGH) {
        BIT_SET(*PORT_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
    } else if (value == LOW) {
        BIT_CLR(*PORT_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
    }
}

uint8_t digitalRead(uint8_t pin)
{
    return BIT_IS_SET(*PIN_REGISTER[getPortNumber(pin)], getPinNumber(pin));
}

void adcSetup()
{
	// set prescaler to 50kHz and 200kHz p 204 --> 8Mhz / 64 = 125kHz
	BIT_SET(ADCSRA, ADPS1); // Datasheet ATmega32 p.216
	BIT_SET(ADCSRA, ADPS2); // Datasheet ATmega32 p.216
	
	// AVCC with external capacitor at AREF pin
	BIT_SET(ADMUX, REFS0); // Datasheet ATmega32 p.214
	BIT_CLR(ADMUX, REFS1); // Datasheet ATmega32 p.214
	
	// Switch on ADC
	BIT_SET(ADCSRA, ADEN); // Datasheet ATmega32 p.216
	
	// ADC Left Adjust Result
	BIT_SET(ADMUX,ADLAR); // Datasheet ATmega32 p.214
}

void setAnalogInputPin (uint8_t pin)
{
	// clear last 5 bits
	ADMUX = ADMUX & 0b11100000;
	switch(pin){
		case 0: ADMUX |= ADC0; break; // Datasheet ATmega32 p.215
		case 1: ADMUX |= ADC1; break; // Datasheet ATmega32 p.215
		case 2: ADMUX |= ADC2; break; // Datasheet ATmega32 p.215
		case 3: ADMUX |= ADC3; break; // Datasheet ATmega32 p.215
		case 4: ADMUX |= ADC4; break; // Datasheet ATmega32 p.215
		case 5: ADMUX |= ADC5; break; // Datasheet ATmega32 p.215
		case 6: ADMUX |= ADC6; break; // Datasheet ATmega32 p.215
		case 7: ADMUX |= ADC7; break; // Datasheet ATmega32 p.215
		default: break;
	}
}

uint8_t adcSingleRun()
{
	// Start ADC Conversion
	BIT_SET(ADCSRA, ADSC); // Datasheet ATmega32 p.216
	while (BIT_IS_SET(ADCSRA, ADSC)) 
	{
		// Wait till ADC Conversion is finish
	}
	return ADCH;
}


uint8_t analogRead(uint8_t pin)
{
	if(pin <= 7) // PA0 - PA7
	{
		uint8_t result = 0;
		adcSetup();
		pinMode(pin, INPUT);
		setAnalogInputPin (pin);
		result = adcSingleRun(); 
		return result;
	}
	return 0;
}

void analogReadFreeRunning(uint8_t pin);

int16_t analogReadLast(uint8_t pin, bool clear);


void pullUpDnControl(uint8_t pin, PullUpDown pud)
{
    if (BIT_IS_SET(*DATA_DIRECTION_REGISTERS[getPortNumber(pin)], getPinNumber(pin)) == 0) {
        if (pud == PUD_UP) {
            BIT_SET(*PORT_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
        } else if (pud == PUD_DOWN) {
            BIT_CLR(*PORT_REGISTERS[getPortNumber(pin)], getPinNumber(pin));
        }
    }
}


void pwmWrite(uint8_t pin, uint8_t dutyCycle)
{
	if (pin == PWM_PIN)
	{
		OCR2 = dutyCycle;
	}
}


unsigned int getPortNumber(uint8_t pin) { return pin / PINS_PER_REGISTER; }

unsigned int getPinNumber(uint8_t pin) { return pin % PINS_PER_REGISTER; }
