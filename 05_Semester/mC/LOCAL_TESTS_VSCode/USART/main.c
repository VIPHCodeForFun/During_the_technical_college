
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "ringtest_V3.h"

RingBuffer TX_BUFFER;

uint8_t usartStringWrite(const char *str)
{
    char *ptrStr = (char *)str;
    uint8_t count = 0;
    while (*ptrStr != '\0')
    {
        ringBufferPush(&TX_BUFFER, *ptrStr);
        ptrStr++;
        count++;
    }
    // enableTransmitBufferEmptyInterrupt();
    // BIT_CLR(UCSRB,TXEN);
    return count;
}

int main()
{
    ringBufferInit(&TX_BUFFER);
    usartStringWrite("Hello Grub");

    RingBuffer save = TX_BUFFER;
    char xxx = 0;
    while (ringBufferPop(&TX_BUFFER, &xxx))
    {
        printf("%c", xxx);
    }

    return 0;
}