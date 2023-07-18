/*
 * spi.h
 *
 * Created: 06.01.2023 16:44:18
 *  Author: Gruber Vidmar
 */ 

#ifndef SPI_H_
#define SPI_H_

#define SS 12	// DDB4
#define MOSI 13	// DDB5
#define MISO 14	// DDB6
#define SCK 15	// DDB7
#define SPI_DEFAULT_BYTE 0x00

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdbool.h>

#include "utils/bit.h"
#include "utils/ring-buffer.h"
#include "avrhal/pin.h"

/** Global Receive Buffer for spi */
RingBuffer SPI_RX_BUFFER;
/** Global Transmit Buffer for spi */
RingBuffer SPI_TX_BUFFER;

/* Sets up a SPI slave Clock Polarity	& Clock Phase are 0 */
void spiSlaveSetup();

/* Writes a uint8_t value to the SPI interface */
bool spiWrite(uint8_t byte);
/* Reads a value from the SPI interface */
bool spiRead(uint8_t* byte);

/* See if data is available for reading */
bool CheckReadDataAvailable();
/* See if data is available to write */
bool CheckWirteIsPosible();



#endif /* SPI_H_ */