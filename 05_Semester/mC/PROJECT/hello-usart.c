#include "avrhal/time.h"
#include "utils/bit.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

static uint8_t Transmitbyte;

static inline void enableTransmitBufferEmptyInterrupt()
{
    BIT_SET(UCSRB, UDRIE); // Datasheet ATmega32 p.161
}

static inline void disableTransmitBufferEmptyInterrupt()
{
    BIT_CLR(UCSRB, UDRIE); // Datasheet ATmega32 p.161
}

ISR(USART_UDRE_vect)
{
	UDR = Transmitbyte;
	disableTransmitBufferEmptyInterrupt();
}

void usartSetup9600()
{
							// 8N1 Default -> Datasheet ATmega32 p.162
    BIT_SET(UCSRB, TXEN);	// Datasheet ATmega32 p.161

    // calculation of baud rate register "UBRR"
    uint32_t baudRate = 9600;
    uint16_t ubrrValue = (F_CPU / (16UL * baudRate)) - 1;	// Datasheet ATmega32 p.162
    UBRRL = ubrrValue;										// Datasheet ATmega32 p.164
    UBRRH = ubrrValue >> 8;									// Datasheet ATmega32 p.164
}

void usartSendWithBusyWait(uint8_t byte)
{
    /* here is waited until the USART interface is free. */
    while (!(BIT_IS_SET(UCSRA, UDRE))) {
    }
    UDR = byte;
}

static const char* data = "Hello World from ATmega32!\r\n";

void sendMessageForever()
{
    uint8_t dataLength = strlen(data);
    uint8_t currentDataIndex = 0;
    uint8_t lineTime = 2000 / strlen(data); // 2000 = 2sek = 0.5Hz
    while (1) {

        /* NO BUSYWAIT */
        enableTransmitBufferEmptyInterrupt();
        Transmitbyte = data[currentDataIndex];
        currentDataIndex++;
        currentDataIndex = currentDataIndex % dataLength;
        delay(lineTime);
    }
}

int main(void)
{
    sei();
    usartSetup9600();
	sendMessageForever();
    return 0;
}
