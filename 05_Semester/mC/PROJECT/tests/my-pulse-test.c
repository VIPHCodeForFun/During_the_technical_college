/*
 * my_timer_test.c
 *
 * Created: 17.11.2022 20:25:14
 *  Author: grubs
 */ 

#include "avrhal/time.h"
#include "avrhal/usart.h"
#include "avrhal/usart-string.h"
#include "avrhal/pin.h"
#include "avrhal/pulse-counter.h"

int main()
{
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	sei();
	pulseCounterSetup();
	
	uint32_t test;
	uint32_t test2;

	
	pinMode(2,1);
	
	while(1)
	{
		digitalWrite(2,1);
		_delay_ms(2);
		digitalWrite(2,0);
		_delay_ms(2);
		pulseCounterResult(&test,&test2);
		_delay_ms(500);
		usartStringPrintln("%d,%d",test,test2);
		
	}
	return 0;
}

