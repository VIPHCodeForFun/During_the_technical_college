#ifndef ring_buffer_common_h_eiXeib4Ein9oo1Qu
#define ring_buffer_common_h_eiXeib4Ein9oo1Qu

#include "utils/ring-buffer.h"

#include <stdint.h>
#include <stdio.h>

/** Helper function: Push multiple values to the given ring buffer
 * @param ringBuffer
 * @param[in] nValue number of values to be pushed
 * @param[in] firstValue the first value to be pushed
 * @param[in] valueIncr  the value increment (n-th value = \n firstValue + (n-1)
 * * \p valueIncr)
 * @return Number of successful pushes
 */
uint16_t pushMultiple(RingBuffer *ringBuffer, const uint16_t nValue,
                      const uint8_t firstValue, const uint8_t valueIncr) {
  uint16_t nValuePushed = 0;
  const uint16_t initialSize = ringBufferSize(ringBuffer);

  for (uint16_t i = 0; i < nValue; ++i) {
    const uint8_t nextValue = firstValue + (i * valueIncr);
    const uint16_t expectedSize = initialSize + (i + 1);

    const bool success = ringBufferPush(ringBuffer, nextValue);
    if (!success || expectedSize != ringBufferSize(ringBuffer)) {
      break;
    }
    nValuePushed += success;
  }

  return nValuePushed;
}

/** Helper function: Pop multiple values from the given ring buffer
 * @param ringBuffer
 * @param[in] nValue number of values to be removed
 * @param[in] expectedFirstValue the expected value of the first removed item
 * @param[in] expectedValueIncr the expected increment from value to value
 * @return Number of matching values according to \p expectedFirstValue and \p
 * expectedValueIncr
 */
uint16_t popMultiple(RingBuffer *ringBuffer, const uint16_t nValue,
                     const uint8_t expectedFirstValue,
                     const uint8_t expectedValueIncr) {
  const uint16_t initialSize = ringBufferSize(ringBuffer);
  uint16_t nValueMatch = 0;
  uint8_t value;

  for (uint16_t i = 0; i < nValue; ++i) {
    const uint8_t expectedValue = expectedFirstValue + (i * expectedValueIncr);
    const uint16_t expectedSize = initialSize - (i + 1);

    const bool success = ringBufferPop(ringBuffer, &value);

    if (!success || expectedSize != ringBufferSize(ringBuffer) ||
        value != expectedValue) {
      break;
    }

    ++nValueMatch;
  }

  return nValueMatch;
}

#endif
