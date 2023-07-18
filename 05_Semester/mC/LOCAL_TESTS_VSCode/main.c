
#define RING_BUFFER_CAPACITY 10

#include <stdio.h>
#include "ringtest_V3.h"

int main()
{
    RingBuffer MyRingBuffer;
    // RingBuffer *PtrMyRingBuffer = &MyRingBuffer;

    uint8_t myVal = 0;

    ringBufferInit(&MyRingBuffer);

    for (size_t i = 10; i < 18; i++)
    {
        ringBufferPush(&MyRingBuffer, i);
    }

    for (size_t i = 0; i < 5; i++)
    {
        ringBufferPop(&MyRingBuffer, &myVal);
        printf("POP  [ %d ]  \n", myVal);
    }
    for (size_t i = 20; i < 30; i++)
    {
        ringBufferPush(&MyRingBuffer, i);
    }

    printf("SIZE  [ %d ]  \n", ringBufferSize(&MyRingBuffer));
    return 0;
}