/*
* In the lab setting, data is transmitted and received using the SPI protocol, with the Raspberry Pi serving as the master device 
* and the Atmega as the slave device. The header file contains both implementations and they are separated using #ifdef 
* preprocessor directive. The received frames have a specific structure that includes a sequence of "keys" followed by a sequence
* of "values". The sent frames can have either no transfer parameters, which consist only of a sequence of "keys", or with 
* transfer parameters, which include a sequence of "keys" followed by a sequence of "values". The Raspberry Pi is responsible for
* controlling the communication and structuring the data as described.
*
* For received frames, they have a specific structure that includes a sequence of "keys" followed by a sequence of "values". 
* The keys and values can represent different types of information, such as commands, sensor readings, or status updates. The 
* format of the received frame is 
* "[key] [key] [value] [value] [value] [key] [key]".
*
* For sent frames, they can have either no transfer parameters, which consist only of a sequence of "keys", or with transfer 
* parameters, which include a sequence of "keys" followed by a sequence of "values". The keys and values can represent different 
* types of information, such as commands, sensor settings, or status requests. The format of the sent frame without transfer 
* parameters is 
* "[key] [key] [key] [key]". 
* The format of the sent frame with transfer parameters is 
* "[key] [key] [value] [value]".
*
* "The OpenAI GPT-based model (ChatGPT)".
* OpenAI website (https://openai.com/)
* the model is hosted (https://github.com/openai/gpt-3)
*/
#ifndef SPI_FAN_PROTOCOL_H_
#define SPI_FAN_PROTOCOL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MESSAGE_SIZE 16
#define SPI_CHAN 0
#define SPI_CLK_SPEED 125000 // Hz
#define DEFAULT_BYTE 0x00

/* RASPBERRY_PI ---------------------------------------------------------  */
#ifdef RASPBERRY_PI

#include <wiringPi.h>
#include <wiringPiSPI.h>

/* Setup a SPI-master on the raspberry 
* Clock Polarity = 0 and Clock Phase = 0
* Surce: http://wiringpi.com/reference/spi-library/ 
*/
bool setupSpi();
/* transmits a key and expects uint8_t response  */
bool transmitKeyReceiveUint8Spi(uint8_t transmitKey, uint8_t *result);
/* transmits a key and expects uint32_t response  */
bool transmitKeyReceiveUint32Spi(uint8_t transmitKey, uint32_t *result);
/* sets the data in the frame to default */
void clearFrame(uint8_t frame[], uint8_t len);
/* prints the frame on the console  */
void printFrame(uint8_t *frame, uint8_t len);
/* divides a uint32_t into 4x uint8_t  */ //  (ChatGPT)
void splitUint32to8(uint32_t frame, uint8_t *byte1, uint8_t *byte2, uint8_t *byte3, uint8_t *byte4);
/* merges 4x uint8_t into one uint32_t */ //  (ChatGPT)
uint32_t mergeUint8to32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
/* Sends a frame with a key and value to the SPI interface. */
bool sendValueFrame(uint8_t transmitKey, uint8_t value);


/* FUNCTIONS */
bool setupSpi(){
	int error = 0;
	error = wiringPiSPISetup(SPI_CHAN, SPI_CLK_SPEED); // http://wiringpi.com/reference/spi-library/
	if (error < 0){
		printf("!! ERROR Setup SPI\n");
		return false;
	}
	return true;
}

bool transmitKeyReceiveUint8Spi(uint8_t transmitKey, uint8_t *result){
	uint8_t frame[MESSAGE_SIZE];
	clearFrame(frame, MESSAGE_SIZE);

	frame[0] = DEFAULT_BYTE;
	frame[1] = transmitKey;
	frame[2] = transmitKey;
	frame[3] = transmitKey;
	frame[4] = transmitKey;

	wiringPiSPIDataRW(SPI_CHAN, frame, MESSAGE_SIZE); // http://wiringpi.com/reference/spi-library/

	bool frameStart = false;
	uint8_t frameStartCount = 0;

	for (uint8_t i = 0; i < MESSAGE_SIZE - 7; i++){
		// Check if first 2 are key
		if (frame[i] == transmitKey && frame[i + 1] == transmitKey){
			// Check if last 2 are key
			if (frame[i + 6] == transmitKey && frame[i + 7] == transmitKey){
				*result = frame[i + 2];
				return true;
			}
		}
	}
	printFrame(frame, MESSAGE_SIZE);
	*result = DEFAULT_BYTE;
	return false;
}

bool transmitKeyReceiveUint32Spi(uint8_t transmitKey, uint32_t *result){
	uint8_t frame[MESSAGE_SIZE];
	clearFrame(frame, MESSAGE_SIZE);

	frame[0] = DEFAULT_BYTE;
	frame[1] = transmitKey;
	frame[2] = transmitKey;
	frame[3] = transmitKey;
	frame[4] = transmitKey;

	wiringPiSPIDataRW(SPI_CHAN, frame, MESSAGE_SIZE); // http://wiringpi.com/reference/spi-library/

	bool frameStart = false;
	uint8_t frameStartCount = 0;

	for (size_t i = 0; i < MESSAGE_SIZE - 7; i++){
		if (frame[i] == transmitKey && frame[i + 1] == transmitKey){
			if (frame[i + 6] == transmitKey && frame[i + 7] == transmitKey){
				*result = mergeUint8to32(frame[i + 2], frame[i + 3], frame[i + 4], frame[i + 5]);
				return true;
			}
		}
	}
	printFrame(frame, MESSAGE_SIZE);
	*result = DEFAULT_BYTE;
	return false;
}

bool sendValueFrame(uint8_t transmitKey, uint8_t value){
	uint8_t frame[MESSAGE_SIZE];
	clearFrame(frame, MESSAGE_SIZE);
	frame[0] = DEFAULT_BYTE;
	frame[1] = transmitKey;
	frame[2] = transmitKey;
	frame[3] = value;
	frame[4] = value;
	frame[5] = value;
	frame[6] = value;
	wiringPiSPIDataRW(SPI_CHAN, frame, MESSAGE_SIZE); // http://wiringpi.com/reference/spi-library/
	return true;
}

bool sendKeyOnly(uint8_t transmitKey){
	uint8_t frame[MESSAGE_SIZE];
	clearFrame(frame, MESSAGE_SIZE);
	frame[0] = DEFAULT_BYTE;
	frame[1] = transmitKey;
	frame[2] = transmitKey;
	frame[3] = transmitKey;
	frame[4] = transmitKey;
	wiringPiSPIDataRW(SPI_CHAN, frame, MESSAGE_SIZE); // http://wiringpi.com/reference/spi-library/
	return true;
}

/* Help functions ************************************************************** */
void clearFrame(uint8_t *frame, uint8_t len){
	for (size_t i = 0; i < len; i++){
		frame[i] = DEFAULT_BYTE;
	}
}

void printFrame(uint8_t *frame, uint8_t len){
	for (size_t i = 0; i < len; i++){
		printf(" [%d]", frame[i]);
	}
	printf("\n");
}
// used ChatGPT
void splitUint32to8(uint32_t frame, uint8_t *byte1, uint8_t *byte2, uint8_t *byte3, uint8_t *byte4){
	*byte1 = (frame & 0x000000FF) >> 0;
	*byte2 = (frame & 0x0000FF00) >> 8;
	*byte3 = (frame & 0x00FF0000) >> 16;
	*byte4 = (frame & 0xFF000000) >> 24;
}
// used ChatGPT
uint32_t mergeUint8to32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4){
	return (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
}
#endif /* END RASPBERRY PI */


/* ATMEGA32  ------------------------------------------------------------  */
#ifdef ATMEGA32

#include "avrhal/spi.h"

/* Writes a uint8_t frame to the SPI interface */
void spiWriteFrame8(uint8_t key, uint8_t value);
/* Writes a uint32_t frame to the SPI interface */
void spiWriteFrame32(uint8_t key, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);

/* Splits a uint32 into 4 uint8 values  (ChatGPT) */
void splitUint32to8(uint32_t frame, uint8_t *byte1, uint8_t *byte2, uint8_t *byte3, uint8_t *byte4);


/* FUNCTIONS */
void spiWriteFrame8(uint8_t key, uint8_t value){
	spiWrite(key);
	spiWrite(key);
	spiWrite(value);
	spiWrite(value);
	spiWrite(value);
	spiWrite(value);
	spiWrite(key);
	spiWrite(key);
}

void spiWriteFrame32(uint8_t key, uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4){
	spiWrite(key);
	spiWrite(key);
	spiWrite(byte1);
	spiWrite(byte2);
	spiWrite(byte3);
	spiWrite(byte4);
	spiWrite(key);
	spiWrite(key);
}
// used ChatGPT
void splitUint32to8(uint32_t frame, uint8_t *byte1, uint8_t *byte2, uint8_t *byte3, uint8_t *byte4){
	*byte1 = (frame & 0x000000FF) >> 0;
	*byte2 = (frame & 0x0000FF00) >> 8;
	*byte3 = (frame & 0x00FF0000) >> 16;
	*byte4 = (frame & 0xFF000000) >> 24;
}
#endif /* END ATMEGA32 */

#endif /* SPI_FAN_PROTOCOL_H_ */