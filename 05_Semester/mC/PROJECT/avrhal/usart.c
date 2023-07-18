#include "avrhal/usart.h"

static void usartEnableReciever()
{
    BIT_SET(UCSRB, RXEN); // Datasheet ATmega32 p.161
    BIT_SET(UCSRB, RXCIE); // Datasheet ATmega32 p.161
}

static void usartEnableTransmitter()
{
    BIT_SET(UCSRB, TXEN); // Datasheet ATmega32 p.161
}

static void enableTransmitBufferEmptyInterrupt()
{
    BIT_SET(UCSRB, UDRIE); // Datasheet ATmega32 p.161
}

static void disableTransmitBufferEmptyInterrupt()
{
    BIT_CLR(UCSRB, UDRIE); // Datasheet ATmega32 p.161
}

void usartSetup(UsartBaudrate baud, UsartConfig config)
{

    ringBufferInit(&RX_BUFFER);
    ringBufferInit(&TX_BUFFER);

    // UMSEL: USART Mode Select, Default "Asynchron"
    // Datasheet ATmega32 p.162

    // if the enum "UsartConfig" gets more Frame types implemented,
    // u can add your case
    switch (config) {
    default:
        // 8N1 Default -> Datasheet ATmega32 p.162
        break;
    }

    // calculation of baud rate register "UBRR"
    uint32_t ubrrValue = (F_CPU / (16UL * baud)) - 1; // Datasheet ATmega32 p.162
    UBRRL = ubrrValue; // Datasheet ATmega32 p.164
    UBRRH = ubrrValue >> 8; // Datasheet ATmega32 p.164

    usartEnableReciever();
    usartEnableTransmitter();
}

uint8_t usartAvailableForRead() { return ringBufferSize(&RX_BUFFER); }

uint8_t usartAvailableForWrite()
{
    return ringBufferCapacity(&TX_BUFFER) - ringBufferSize(&TX_BUFFER);
}

bool usartPeek(uint8_t* byte) { return ringBufferPeek(&RX_BUFFER, byte); }

bool usartRead(uint8_t* byte)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { return ringBufferPop(&RX_BUFFER, byte); }
    return false;
}

uint8_t usartReadBytes(uint8_t* bytes, uint8_t maxRead)
{
    uint8_t count = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        for (int i = 0; i < maxRead; i++) {
            if (ringBufferPop(&RX_BUFFER, bytes) == true) {
                count++;
                bytes++;
            } else {
                return count;
            }
        }
    }
    return count;
}

bool usartWrite(uint8_t byte)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {

        if (ringBufferPush(&TX_BUFFER, byte) == true) {
            enableTransmitBufferEmptyInterrupt();
            return true;
        }
    }

    return false;
}

void usartFlush()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        while (!(ringBufferEmpty(&TX_BUFFER))) {
            enableTransmitBufferEmptyInterrupt();
        }
    }
}

ISR(USART_UDRE_vect) // Interrupt UDRE: used for Transmit USART
{
    uint8_t data = 0;
    if (ringBufferPop(&TX_BUFFER, &data) == true) {
        UDR = data;
    } else // Ring buffer is EMPTY
    {
        disableTransmitBufferEmptyInterrupt();
    }
}

ISR(USART_RXC_vect)	// Interrupt RXC: used for Receive USART
{
    uint8_t data = UDR;
    ringBufferPush(&RX_BUFFER, data);
}
