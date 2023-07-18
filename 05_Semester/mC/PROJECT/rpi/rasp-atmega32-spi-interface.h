/*
* The header file is responsible for determining how data is handled from the SPI interface. 
* It is written in such a way that it works for both the sender (Raspberry Pi) and the receiver (Atmega). 
* To achieve this, the header file makes use of the #ifdef preprocessor directive. This allows for separate sections 
* of code to be included or excluded based on the defined macro, allowing the same header file to be used for both the 
* Raspberry Pi and Atmega while handling the data from the SPI interface differently.
* 
* "The OpenAI GPT-based model (ChatGPT)".
* OpenAI website (https://openai.com/)  
* the model is hosted (https://github.com/openai/gpt-3) 
*/

#ifndef RASP_ATMEGA32_SPI_INTERFACE_H_
#define RASP_ATMEGA32_SPI_INTERFACE_H_

#include <stdio.h>
#include <stdint.h>

#include "spi_fan_protocol.h"

/* RASPBERRY_PI ---------------------------------------------------------  */
#ifdef RASPBERRY_PI
/* Set up SPI Slave */
void setupInterface();
/* Print program help */
void showOptions();
/* Get current PWM duty cycle */
void getCurrentPwm();
/* Set current PWM duty cycle (value range: 0 - 255). */
void setCurrentPwm(uint8_t pwm);
/*  Release PWM duty cycle control */
void releasePwmDutyCycle();
/* Get current fan RPM */
void getCurrentFanRpm();


void setupInterface(){
	setupSpi();
}


void getCurrentPwm(){
	uint8_t key = 'p';
	uint8_t pwm = 0;

	printf("Get current PWM duty cycle. 'p'\n");
	if (transmitKeyReceiveUint8Spi(key, &pwm)){
		printf("PWM duty cycle: %d/255\n", pwm);
		printf("Success.\n");
	} 
	else {
		printf("!! Error if (transmitKeyReceiveUint8Spi(key, &pwm))\n");
	}
}


void setCurrentPwm(uint8_t pwm){
	printf("Set PWM duty cycle. 's' %d\n", pwm);
	uint8_t key = 's';
	uint8_t check = 0;
	printf("Set current PWM duty cycle (value range: 0 - 255).\n");
	sendValueFrame(key, pwm);
}


void releasePwmDutyCycle(){
	uint8_t key = 'r';
	sendKeyOnly(key);
	printf("Release PWM duty cycle control.\n");
}


void getCurrentFanRpm(){
	printf("Get current fan RPM.\n");
	uint8_t key = 't';
	uint32_t rpm = 0;
	if (transmitKeyReceiveUint32Spi(key, &rpm)){
		printf("Current Fan RPM = %d \n", rpm);
		printf("Success.\n");
	}
	else {
		printf("!! Error if (transmitKeyReceiveByteSpi(key, &pwm))\n");
	}
}


void showOptions()
{
	printf("OPTIONS: \n");
	printf("-h | <no option>   Print this help.\n");
	printf("-p                 Get current PWM duty cycle.\n");
	printf("-s BYTE            Set current PWM duty cycle (value range: 0 - 255).\n");
	printf("-r                 Release PWM duty cycle control.\n");
	printf("-t                 Get current fan RPM.\n");
}
#endif /* END RASPBERRY PI */

/* ATMEGA32  ------------------------------------------------------------  */
#ifdef ATMEGA32

#include "rpi/spi_fan_protocol.h"
#include <stdlib.h>

/* Sets up the SPI interface */
void setupInterface();
/* SPI interface between ATmega32 and raspberrypi  */
void spiInterface(uint8_t dutCycle, uint8_t *spiAdcvalue, bool *spiSendingAktive, uint32_t rpm);


void setupInterface(){
	spiSlaveSetup();
}

void spiInterface(uint8_t dutCycle, uint8_t *spiAdcvalue, bool *spiSendingAktive, uint32_t rpm){
	uint8_t p = 0;
	uint8_t s = 0;
	uint8_t r = 0;
	uint8_t t = 0;
	
	while (CheckReadDataAvailable() == true)
	{
		uint8_t spiReadData = SPI_DEFAULT_BYTE;
		spiRead(&spiReadData);
		
		if (spiReadData == 'p'){
			p++;
			if (p == 4){
				p = 0;
				spiWriteFrame8('p', dutCycle);
				usartStringPrintln("Master 'p' return dutCycle %d", dutCycle);
			}
		}
		
		if (spiReadData == 's')
		{
			s++;
			if (s == 2)
			{
				s = 0;
				spiRead(spiAdcvalue);
				usartStringPrintln("Master 's' %d --> is set  ",*spiAdcvalue);
				*spiSendingAktive = true;
			}
		}
		if (spiReadData == 'r'){
			r++;
			if (r == 4){
				r = 0;
				*spiSendingAktive = false;
				usartStringPrintln("Release control ...");
			}
		}
		if (spiReadData == 't')
		{
			t++;
			if (t == 4){
				t = 0;
				uint8_t frame32[4];
				splitUint32to8(rpm, &frame32[0], &frame32[1], &frame32[2], &frame32[3]);
				spiWriteFrame32('t',frame32[0], frame32[1], frame32[2], frame32[3] );
				usartStringPrintln("Master 't' -> fan RPM. %d", rpm);
			}
		}
	}
}
#endif /* END ATMEGA32 */

#endif /* RASP_ATMEGA32_SPI_INTERFACE_H_ */