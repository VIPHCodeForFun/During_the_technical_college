/**
 * @author Mathias Gruber, Philipp Vidmar :-)
 * @brief A lightweight header-only ringbuffer implementation
 *
 */

#ifndef ring_buffer_h_Opee6yieGhiph2Du
#define ring_buffer_h_Opee6yieGhiph2Du

#include <stdbool.h>
#include <stdint.h>

#ifndef RING_BUFFER_CAPACITY
/* Define size of ring buffer with a default value. */
#define RING_BUFFER_CAPACITY 128
#endif

/** A struct for storing the data for the ringbuffer
 */
typedef struct
{
    uint8_t Buffer[RING_BUFFER_CAPACITY];
    uint8_t BufferLen;
    uint8_t *PtrRead;
    uint8_t *PtrWrite;
    uint8_t *PtrFirstElement;
    uint8_t *PtrLastElement;
    uint8_t CurrentUsedSlots;
} RingBuffer;

/** Initialize the given RingBuffer struct.
 * @param ringBuffer The RingBuffer instance
 * @note Must be called before the ring buffer is used.
 */
static inline void ringBufferInit(RingBuffer *ringBuffer)
{
    ringBuffer->BufferLen = RING_BUFFER_CAPACITY;
    ringBuffer->PtrFirstElement = &ringBuffer->Buffer[0];
    ringBuffer->PtrLastElement = &ringBuffer->Buffer[ringBuffer->BufferLen - 1]; // count starts by 0
    ringBuffer->PtrRead = ringBuffer->PtrFirstElement;
    ringBuffer->PtrWrite = ringBuffer->PtrFirstElement;
    ringBuffer->CurrentUsedSlots = 0;
}

/** Returns the number of elements in the ring buffer.
 * @param ringBuffer The RingBuffer instance
 * @return Number of elements
 */
static inline uint8_t ringBufferSize(const RingBuffer *ringBuffer)
{
    return ringBuffer->CurrentUsedSlots;
}

/** Returns the number of elements which can be stored at maximum.
 * @return Number of elements
 */
static inline uint8_t ringBufferCapacity()
{
    return RING_BUFFER_CAPACITY;
}

/** Checks if the ring buffer has no elements
 * @param ringBuffer The RingBuffer instance
 * @return  True if empty, false otherwise
 */
static inline bool ringBufferEmpty(const RingBuffer *ringBuffer)
{
    if (ringBuffer->CurrentUsedSlots == 0)
    {
        return true;
    }
    return false;
}

/** Checks if the ring buffer is full.
 * @param ringBuffer The RingBuffer instance
 * @return  True if full, false otherwise
 */
static inline bool ringBufferFull(const RingBuffer *ringBuffer)
{
    if (ringBuffer->CurrentUsedSlots == ringBuffer->BufferLen)
    {
        return true;
    }
    return false;
}

/** Pushes the given value to the ring buffer.
 * @param ringBuffer The RingBuffer instance
 * @param[in] value The element to be added
 * @return  True if successful, false otherwise
 */
static inline bool ringBufferPush(RingBuffer *ringBuffer, uint8_t value)
{
    if (ringBufferFull(ringBuffer) == true)
    {
        return false;
    }
    ringBuffer->CurrentUsedSlots++;

    // Write the value into the free space of write-ptr.
    *ringBuffer->PtrWrite = value;

    // Jump forward with the write-prt.
    if (ringBuffer->PtrWrite == ringBuffer->PtrLastElement)
    {
        ringBuffer->PtrWrite = ringBuffer->PtrFirstElement;
    }
    else
    {
        ringBuffer->PtrWrite++;
    }
    return true;
}

/** Returns the oldest value from the ring buffer, without removing it.
 * @param ringBuffer The RingBuffer instance
 * @param[out] value The oldest value
 * @return  True if successful, false otherwise
 */
static inline bool ringBufferPeek(RingBuffer *ringBuffer, uint8_t *value)
{
    if (ringBufferEmpty(ringBuffer) == true)
    {
        return false;
    }

    *value = *ringBuffer->PtrRead;

    return true;
}

/** Removes the oldest value from the ring buffer.
 * @param ringBuffer The RingBuffer instance
 * @param[out] value The removed value
 * @return  True if successful, false otherwise
 */
static inline bool ringBufferPop(RingBuffer *ringBuffer, uint8_t *value)
{
    if (ringBufferEmpty(ringBuffer) == true)
    {
        return false;
    }
    ringBuffer->CurrentUsedSlots--;

    // Read the current value from the read-ptr.
    *value = *ringBuffer->PtrRead;

    // Jump forward with the read-prt.
    if (ringBuffer->PtrRead == ringBuffer->PtrLastElement)
    {
        ringBuffer->PtrRead = ringBuffer->PtrFirstElement;
    }
    else
    {
        ringBuffer->PtrRead++;
    }

    return true;
}
#endif