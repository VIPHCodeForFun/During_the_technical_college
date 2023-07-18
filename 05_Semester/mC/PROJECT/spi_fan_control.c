/*
 * my_spi_slave_test.c
 *
 * Created: 10.01.2023 13:44:00
 *  Author: phili
 */ 
#define ATMEGA32

#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "avrhal/fan.h"
#include "avrhal/pin.h"
#include "avrhal/time.h"
#include "utils/led-bar.h"
#include "rpi/rasp-atmega32-spi-interface.h"

#include <stdlib.h>

#define LED_BAR_FIRST_PIN 1
#define LED_BAR_NLEDS 7

int main(){
	uint8_t adcValue = 0;
	uint8_t spiAdcvalue = 0;
	bool spiSendingAktive = false;
	
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	setupInterface();
	fanSetup();
	ledBarSetup(LED_BAR_NLEDS,LED_BAR_FIRST_PIN);
	
	sei();		 // Enable Global Interrupts
	
	while ( 1 ){
		for(int i = 0; i < 4 ; i++){ // 4 times = 1 Second
			if (spiSendingAktive == false){
				adcValue = analogRead(0);		
			}
			else{
				adcValue = spiAdcvalue;
			}
			setFanSpeed(PWM_PIN,adcValue);
			ledBarSet(adcValue);
			_delay_ms(250); // milliseconds
		}
		
		uint32_t rpm = getFanSpeed();
		uint8_t dutCycle = adcValue;
		uint32_t mVolt = 19.53 * adcValue; // 19.53 mVolt per adcValue
		uint8_t raw = adcValue;
		uint32_t upTime = millis() / 1000; // from milli to secs
		usartStringPrintln("Speed: %lu rpm, DutyCycle: %d/255, Poti: %lu mV (raw: %d), Uptime: %lu s",rpm ,dutCycle, mVolt, raw, upTime);
		
		spiInterface(dutCycle, &spiAdcvalue, &spiSendingAktive, rpm);
	}
}
		
		