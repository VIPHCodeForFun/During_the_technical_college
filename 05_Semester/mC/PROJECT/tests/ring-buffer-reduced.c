#include "utils/bit.h"
#define RING_BUFFER_CAPACITY 128
#include "tests/ring-buffer-common.h"
#include "utils/ring-buffer.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

bool testRingBufferPushPopMultiple() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  // Pushing multiple values and removing them again ...
  const uint8_t nValueExpected = ringBufferCapacity();
  const uint16_t nValuePushed =
      pushMultiple(&ringBuffer, nValueExpected, 1, 50);
  success &= (nValuePushed == nValueExpected);

  const uint16_t nValueMatch = popMultiple(&ringBuffer, nValueExpected, 1, 50);
  success &= (nValueMatch == nValueExpected);
  return success;
}

bool testRingBufferPushBeyond() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  // Trying to push the buffer beyond its capacity, the number of successful
  // pushes must match the buffer capacity
  const uint8_t firstValue = 1;
  const uint16_t nValuePushed =
      pushMultiple(&ringBuffer, 2 * ringBufferCapacity(), firstValue, 30);
  success &= (nValuePushed == ringBufferCapacity());

  // The first value still must be present (not overwritten)
  uint8_t value = 0;
  success &= ringBufferPop(&ringBuffer, &value);
  success &= (value == firstValue);

  return success;
}

bool testRingBufferPopEmpty() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  const uint8_t expectedValue = 42;

  {
    // Given an empty buffer, removing a value must not be possible.
    uint8_t value = expectedValue;
    success &= !ringBufferPop(&ringBuffer, &value);
    // The passed value is expected to remain unmodified.
    success &= (value == expectedValue);
  }
  {
    // Test if the same works with a buffer that has been non-empty before
    const uint8_t nValueExpected = 5;
    const uint16_t nValuePushed =
        pushMultiple(&ringBuffer, nValueExpected, 1, 1);
    success &= (nValuePushed == nValueExpected);

    const uint16_t nValueTooMany = nValueExpected * 10;
    const uint16_t nValueMatch = popMultiple(&ringBuffer, nValueTooMany, 1, 1);
    success &= (nValueMatch == nValueExpected);
  }
  return success;
}

bool testRingBufferSize() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  {
    // The size should increase with every pushed element.
    for (uint16_t i = 0; i < ringBufferCapacity(); ++i) {
      success &= (ringBufferSize(&ringBuffer) == i);
      ringBufferPush(&ringBuffer, i);
    }
  }
  {
    // When pushing beyond the capacity, the size must stay the same.
    success &= !ringBufferPush(&ringBuffer, 128);
    success &= (ringBufferSize(&ringBuffer) == ringBufferCapacity());
  }
  {
    // Removing values, the size should reach zero again.
    for (int i = 0; i < ringBufferCapacity(); ++i) {
      uint8_t value = 255;
      ringBufferPop(&ringBuffer, &value);
      success &= (i == value);
      success &= (ringBufferSize(&ringBuffer) == ringBufferCapacity() - i - 1);
    }
    success &= (ringBufferSize(&ringBuffer) == 0);
  }
  {
    // With an empty buffer, size must remain zero when attempting to remove a
    // value
    uint8_t value = 255;
    success &= !ringBufferPop(&ringBuffer, &value);
    success &= (ringBufferSize(&ringBuffer) == 0);
  }
  return success;
}

bool testRingBufferEmpty() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  {
    // A fresh buffer should be empty.
    success &= (ringBufferEmpty(&ringBuffer));
  }
  {
    // Already with one value pushed, the buffer is no longer empty
    success &= ringBufferPush(&ringBuffer, 123);
    success &= (!ringBufferEmpty(&ringBuffer));
  }
  {
    /// Removing the value, the buffer must be empty again
    uint8_t value = 0;
    success &= ringBufferPop(&ringBuffer, &value);
    success &= (ringBufferEmpty(&ringBuffer));
  }
  return success;
}

bool testRingBufferFull() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  {
    // A fresh buffer is not full  (it must be empty :-) )
    success &= (!ringBufferFull(&ringBuffer));
  }
  {
    // Pushing values until the reported capacity has been reached. The buffer
    // must be full now.
    const uint8_t nValuePushed =
        pushMultiple(&ringBuffer, ringBufferCapacity(), 0, 2);
    success &= (nValuePushed == ringBufferCapacity());
    success &= (ringBufferFull(&ringBuffer));
  }
  {
    // Removing a single value, the buffer should no longer be full.
    uint8_t value = 0;
    success &= ringBufferPop(&ringBuffer, &value);
    success &= (!ringBufferFull(&ringBuffer));
  }
  return success;
}

bool testRingBufferPeek() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  const uint8_t expectedValue = 42;

  {
    // Given an empty buffer, peek must return false
    uint8_t value = expectedValue;
    success &= !ringBufferPeek(&ringBuffer, &value);
    // Again, the passed value is expected to remain unmodified.
    success &= (value == expectedValue);
  }
  {
    // When we peek a value, it must remain in the buffer and the size must be
    // unchanged First, push a few values
    const uint8_t nValue = 5;
    const uint8_t firstValue = expectedValue;

    pushMultiple(&ringBuffer, nValue, firstValue, 1);
    success &= (ringBufferSize(&ringBuffer) == nValue);

    // The value may be "peeked"  a few times, the value itself and the buffer
    // size must remain unchanged.
    const uint8_t peekSeveralTimes = 4;

    for (uint8_t i = 0; i < peekSeveralTimes; ++i) {
      uint8_t value = 0;
      success &= ringBufferPeek(&ringBuffer, &value);
      success &= (value == expectedValue);
      success &= (ringBufferSize(&ringBuffer) == nValue);
    }
  }
  return success;
}

bool testRunInCircles() {
  // This test checks the correct wrapping of the internal buffer read and write
  // positions

  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);
  bool success = true;

  const uint8_t nValueMax = ringBufferCapacity();

  for (uint8_t nValue = 1; nValue < nValueMax; ++nValue) {

    const uint32_t nRun = (ringBufferCapacity() + 1) / nValue * 10;

    for (uint32_t i = 0; i < nRun; ++i) {
      // Pushing multiple values and removing them again ...
      const uint16_t nValuePushed = pushMultiple(&ringBuffer, nValue, 1, 50);
      success &= (nValuePushed == nValue);

      const uint16_t nValueMatch = popMultiple(&ringBuffer, nValue, 1, 50);
      success &= (nValueMatch == nValue);
    }
  }
  return success;
}

/** Running all specified tests
 * @return A bit field where each failed test is marked as '1'. On success the
 * value 0 is returned.
 */
uint8_t runTests() {
  typedef bool (*TestFunction)(void);

  TestFunction tests[] = {testRingBufferPushPopMultiple,
                          testRingBufferPushBeyond,
                          testRingBufferPopEmpty,
                          testRingBufferSize,
                          testRingBufferEmpty,
                          testRingBufferFull,
                          testRingBufferPeek,
                          testRunInCircles};
  uint8_t result = 0;

  for (uint8_t i = 0; i < ARRAY_SIZE(tests); ++i) {
    const bool success = tests[i](); // Run the test
    if (!success) {
      BIT_SET(result, i);
      PORTA = result;
    }
  }
  return result;
}

void visualizeSuccess() {
  for (uint8_t i = 0; i < 36; ++i) {
    PORTA = ((8 >> (i & 3)) | (16 << (i & 3))) |
            (255 << i / 4 >> 8 | 255 << 8 >> i / 4);
    _delay_ms(100);
  }
  PORTA = 0;
}

int main() {
  DDRA = 0xFF;
  PORTA = 0;

  while (1) {
    const uint8_t result = runTests();
    const uint8_t failure = (result != 0);

    if (failure) {
      PORTA = result; // Show all failed tests on the LED panel.
    } else {
      visualizeSuccess();
    }
  }
}
