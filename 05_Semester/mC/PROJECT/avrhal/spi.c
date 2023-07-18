/*
 * spi.c
 * Created: 06.01.2023 16:44:18
 * Author: Gruber Vidmar
 */ 
#include "avrhal/spi.h"

void spiSlaveSetup(){
	ringBufferInit(&SPI_RX_BUFFER);
	ringBufferInit(&SPI_TX_BUFFER);
	
	/* Set IMPUT (SLAVE) */
	pinMode(SCK, INPUT);	// Datasheet ATmega32 p.57
	pinMode(MOSI, INPUT);	// Datasheet ATmega32 p.58
	pinMode(SS, INPUT);		// Datasheet ATmega32 p.58
	
	/* Set OUTPUT (SLAVE) */
	pinMode(MISO, OUTPUT);	// Datasheet ATmega32 p.57
	
	/* Configure the SPI module */
	BIT_CLR(SPCR, MSTR); // Slave Select		Datasheet ATmega32 p.137
	BIT_CLR(SPCR, CPOL); // Clock Polarity		Datasheet ATmega32 p.137
	BIT_CLR(SPCR, CPHA); // Clock Phase			Datasheet ATmega32 p.137

	/* Enable the SPI module */
	BIT_SET(SPCR, SPE);		// Datasheet ATmega32 p.136
	
	/* Enable SPI Interupt */
	BIT_SET(SPCR, SPIE);	// Datasheet ATmega32 p.136
	
	SPDR = SPI_DEFAULT_BYTE;
}


bool spiWrite(uint8_t byte){
	if(CheckWirteIsPosible() == true){
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
			ringBufferPush(&SPI_TX_BUFFER, byte);
		}
		return true;
	}
	return false;
}


bool spiRead(uint8_t* byte){
	if (CheckReadDataAvailable() == true){
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			ringBufferPop(&SPI_RX_BUFFER, byte);
		}
		return true;
	}	
	return false;
}


bool CheckReadDataAvailable(){
	if (ringBufferEmpty(&SPI_RX_BUFFER) == true){
		return false;
	}
	return true;
}


bool CheckWirteIsPosible(){
	if (ringBufferFull(&SPI_TX_BUFFER) == true){
		return false;
	}
	return true;
}


ISR(SPI_STC_vect){
	/* Get received data */
	uint8_t receivedData = SPDR;
	ringBufferPush(&SPI_RX_BUFFER, receivedData);

    /* Send response data */
    uint8_t responseData = SPI_DEFAULT_BYTE;
	if (ringBufferPop(&SPI_TX_BUFFER, &responseData) == true) {
		 SPDR = responseData;
	} 
}