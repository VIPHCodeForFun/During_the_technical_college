/*
 * fac.c
 *
 * Created: 25.11.2022 21:17:55
 *  Author: Matthias Gruber, Philipp Vidmar
 */

#include "fan.h"

void fanSetup()
{
	// Pin 31 is the dedicated PWM-Pin
    pinMode(31, PWM_OUTPUT);
    setupPWM();
    pulseCounterSetup();
}

void setFanSpeed(uint8_t pin, uint8_t speed)
{
    pwmWrite(pin, speed);
}

uint32_t getFanSpeed()
{
    uint32_t pulses;
    uint32_t time;
    pulseCounterResult(&pulses, &time);

    uint32_t rpm;
	
	// ***Calculation from pulses to Revolutions
	// and microsecs to secs. 
	rpm = (pulses / 2) / (time / 1000000) * 60;

    return rpm;
}
