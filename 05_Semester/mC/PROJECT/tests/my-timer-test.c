/*
 * my_pulse_test.c
 *
 * Created: 25.11.2022 18:18:35
 *  Author: grubs
 */ 

#include "avrhal/time.h"
#include "avrhal/usart.h"
#include "avrhal/usart-string.h"

int main()
{
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	sei();
	timeSetup();

	
	while(1)
	{
		usartStringPrintln("MilliSeks: %lu  MicroSekonds: %ld)",millis(),micros());
		_delay_ms(200);
	}
	return 0;
}