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
#include "utils/led-bar.h"
#include <stdlib.h>

#define LED_BAR_FIRST_PIN 1
#define LED_BAR_NLEDS 7

int main()
{
	uint8_t adcValue = 0;
	
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	fanSetup();
	ledBarSetup(LED_BAR_NLEDS,LED_BAR_FIRST_PIN); 
	
	sei();
	
	usartStringPrintln("Start fan-control.c");
	while(1)
	{
		for(int i = 0; i < 4 ; i++)
		{
		adcValue = analogRead(0);
		setFanSpeed(PWM_PIN,adcValue);
		ledBarSet(adcValue);
		 _delay_ms(250);
		}
		
		uint32_t rpm = getFanSpeed(); 
		uint8_t dutCycle = adcValue;
		uint32_t mVolt = 19.53 * adcValue;
		uint8_t raw = adcValue;
		uint32_t upTime = millis() / 1000; // from milli to secs
		
		usartStringPrintln("Speed: %lu rpm, DutyCycle: %d/255, Poti: %lu mV (raw: %d), Uptime: %lu s",rpm ,dutCycle, mVolt, raw, upTime);
	}
}
