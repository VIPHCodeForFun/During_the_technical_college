/*
 * my_spi_slave_test.c
 *
 * Created: 10.01.2023 13:44:00
 *  Author: phili
 */ 


#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "avrhal/spi.h"
#include "avrhal/fan.h"
#include "utils/led-bar.h"
#include "avrhal/pin.h"
#include "avrhal/time.h"

#include <stdlib.h>

#define LED_BAR_FIRST_PIN 1
#define LED_BAR_NLEDS 7


int main()
{
	usartSetup(USART_B9600, USART_CONFIG_8N1);
	spiSlaveSetup();

	fanSetup();
	ledBarSetup(LED_BAR_NLEDS,LED_BAR_FIRST_PIN);
	
	sei(); // Enable Global Interrupts
	
	usartStringPrintln("Start fan-control.c");
	
	uint8_t array[3];
	uint8_t waitTime = 100;
	
	while ( 1 )
	{
		
		if (CheckReadDataAvailable() == true)
		{
			array[0] = 0x00;
			array[1] = 0x00;
			array[2] = 0x00;
			
			uint8_t count = 0;
			
			delay(waitTime);
			usartStringPrintln("* Wait for 1 Sekond for message");
			uint16_t breakTime = 0;
			while ( count < 3 )
			{
				if (spiRead(&array[count]) == true)
				{
					uint8_t temp = array[count];
					
					if ( temp == 1 || temp == 2 || temp == 3 )
					{
						count++;
					}
					spiWrite(SPI_DEFAULT_BYTE);
					delay(waitTime);
				}
				breakTime = breakTime + 100;
				if (breakTime > 1000)
				{
					delay(waitTime);
					usartStringPrintln(" breakTime");
					break;
				}
			}
			usartStringPrintln("* Message was successfully received");
			delay(waitTime);
			usartStringPrintln("ATmega SPI Write [%d]  [%d]  [%d]", 0x00, 0x00, 0x00);
			delay(waitTime);
			usartStringPrintln("ATmega SPI Read  [%d]  [%d]  [%d]", array[0], array[1], array[2]);
			delay(waitTime);
			usartStringPrintln("* Send a new message to Master");
			delay(waitTime);
			
			if ( array[0] == 1 && array[1] == 2 && array[2] == 3 )
			{
				
				array[0] = 0x04;
				array[1] = 0x05;
				array[2] = 0x06;
				for (int i = 0; i < 3; i++)
				{
					spiWrite(array[i]);
				}
				
			}
			usartStringPrintln("* Message was successfully received");
			delay(waitTime);
			usartStringPrintln("ATmega SPI Write [%d]  [%d]  [%d]", array[0], array[1], array[2]);
			delay(waitTime);
			usartStringPrintln("ATmega SPI Read  [%d]  [%d]  [%d]", 0x00, 0x00, 0x00);
		} 
		else
		{
			usartStringPrintln("Nothing to read");
		}
		delay(waitTime);
	}
}		
		
		
		/*
		// EMPFANGEN 
		uint8_t spiReadData = SPI_DEFAULT_BYTE;
		spiRead(&spiReadData);
		usartStringPrintln("Atmega32 SPI ReadData  = %c", spiReadData);
		
		// SENDEN
		uint8_t spiWriteData = 'X';
		spiWrite(spiWriteData);
		usartStringPrintln("Atmega32 SPI WriteData = %c", spiWriteData);
		*/
		
		
	

		/*
		
		uint8_t spiWriteData = 'C';
		spiWrite(spiWriteData);
		usartStringPrintln("write = %c", spiWriteData);
		*/