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
#include "avrhal/pin.h"
#include <stdlib.h>

int main()
{
	uint8_t result = 0;
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	
	sei();
	usartStringPrintln("Start");
	while(1)
	{
		result = analogRead(0);
		_delay_ms(1000);
		usartStringPrintln("result: %d ",result);

	}
}

