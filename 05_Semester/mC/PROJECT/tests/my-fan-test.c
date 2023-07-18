/*
 * my_fan_test.c
 *
 * Created: 25.11.2022 21:41:03
 *  Author: grubs
 */ 

#include "avrhal/fan.h"
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "avrhal/pulse-counter.h"
#include "avrhal/pin.h"
#include <stdlib.h>

int main()
{
	uint32_t rpm = 0;
	uint32_t pwm20 = 51;
	uint32_t pwm50 = 128;
	uint32_t pwm100 = 255;
	
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	fanSetup();
	
	sei();
	usartStringPrintln("Start");
	while(1)
	{
		
		setFanSpeed(PWM_PIN,pwm20);
		_delay_ms(10000);
		rpm = getFanSpeed();
		usartStringPrintln("20 PWM: %lu RPM: %lu",pwm20 ,rpm);
		
		
		setFanSpeed(PWM_PIN,pwm50);
		_delay_ms(10000);
		rpm = getFanSpeed();
		usartStringPrintln("50 PWM: %lu RPM: %lu",pwm50 ,rpm);
		
		
		setFanSpeed(PWM_PIN,pwm100);
		_delay_ms(10000);
		rpm = getFanSpeed();
		usartStringPrintln("100 PWM: %lu RPM: %lu",pwm100 ,rpm);

	}
}

