#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define RING_BUFFER_CAPACITY 233u // Leave unchanged
#include "tests/ring-buffer-common.h"
#include "utils/ring-buffer.h"

#define ASSERT_EQUAL_INT(x, y)                                                 \
  {                                                                            \
    if (x != y) {                                                              \
      printf("Not equal :-(  ... %d != %d\n", x, y);                           \
    };                                                                         \
    assert(x == y);                                                            \
  }

void testRingBufferCapacity() {
  // The capacity is supposed to match the RING_BUFFER_CAPACITY define.
  // Depending on the employed "full" detection, it might be 1 smaller though.
  const int diff = RING_BUFFER_CAPACITY - ringBufferCapacity();
  assert(diff == 0 || diff == 1);
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferPushPopSingle() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  // Pushing a single value and removing it again ...
  const uint8_t expectedValue = 42;
  bool success = ringBufferPush(&ringBuffer, expectedValue);
  assert(success);

  uint8_t value = 0;
  success = ringBufferPop(&ringBuffer, &value);
  assert(success);
  ASSERT_EQUAL_INT(value, expectedValue);
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferPushPopMultiple() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  // Pushing multiple values and removing them again ...
  const uint8_t nValueExpected = ringBufferCapacity();
  const uint16_t nValuePushed =
      pushMultiple(&ringBuffer, nValueExpected, 1, 50);
  assert(nValuePushed == nValueExpected);

  const uint16_t nValueMatch = popMultiple(&ringBuffer, nValueExpected, 1, 50);
  assert(nValueMatch == nValueExpected);
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferPushBeyond() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  // Trying to push the buffer beyond its capacity, the number of successful
  // pushes must match the buffer capacity
  const uint8_t firstValue = 1;
  const uint16_t nValuePushed =
      pushMultiple(&ringBuffer, 2 * ringBufferCapacity(), firstValue, 30);
  assert(nValuePushed == ringBufferCapacity());

  // The first value still must be present (not overwritten)
  uint8_t value = 0;
  const bool success = ringBufferPop(&ringBuffer, &value);
  assert(success);
  ASSERT_EQUAL_INT(value, firstValue);

  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferPopEmpty() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  const uint8_t expectedValue = 42;

  {
    // Given an empty buffer, removing a value must not be possible.
    uint8_t value = expectedValue;
    const bool success = ringBufferPop(&ringBuffer, &value);
    assert(!success);
    // The passed value is expected to remain unmodified.
    assert(value == expectedValue);
  }
  {
    // Test if the same works with a buffer that has been non-empty before
    const uint8_t nValueExpected = 5;
    const uint16_t nValuePushed =
        pushMultiple(&ringBuffer, nValueExpected, 1, 1);
    assert(nValuePushed == nValueExpected);

    const uint16_t nValueTooMany = nValueExpected * 10;
    const uint16_t nValueMatch = popMultiple(&ringBuffer, nValueTooMany, 1, 1);
    assert(nValueMatch == nValueExpected);
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferSize() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  {
    // The size should increase with every pushed element.
    for (uint16_t i = 0; i < ringBufferCapacity(); ++i) {
      assert(ringBufferSize(&ringBuffer) == i);
      ringBufferPush(&ringBuffer, i);
    }
  }
  {
    // When pushing beyond the capacity, the size must stay the same.
    const bool success = ringBufferPush(&ringBuffer, 128);
    assert(!success);
    assert(ringBufferSize(&ringBuffer) == ringBufferCapacity());
  }
  {
    // Removing values, the size should reach zero again.
    for (int i = 0; i < ringBufferCapacity(); ++i) {
      uint8_t value = 255;
      ringBufferPop(&ringBuffer, &value);
      assert(i == value);
      assert(ringBufferSize(&ringBuffer) == ringBufferCapacity() - i - 1);
    }
    assert(ringBufferSize(&ringBuffer) == 0);
  }
  {
    // With an empty buffer, size must remain zero when attempting to remove a
    // value
    uint8_t value = 255;
    const uint8_t success = ringBufferPop(&ringBuffer, &value);
    assert(!success);
    assert(ringBufferSize(&ringBuffer) == 0);
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferEmpty() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  {
    // A fresh buffer should be empty.
    assert(ringBufferEmpty(&ringBuffer));
  }
  {
    // Already with one value pushed, the buffer is no longer empty
    const bool success = ringBufferPush(&ringBuffer, 123);
    assert(success);
    assert(!ringBufferEmpty(&ringBuffer));
  }
  {
    /// Removing the value, the buffer must be empty again
    uint8_t value = 0;
    const bool success = ringBufferPop(&ringBuffer, &value);
    assert(success);
    assert(ringBufferEmpty(&ringBuffer));
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferFull() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  {
    // A fresh buffer is not full  (it must be empty :-) )
    assert(!ringBufferFull(&ringBuffer));
  }
  {
    // Pushing values until the reported capacity has been reached. The buffer
    // must be full now.
    const uint8_t nValuePushed =
        pushMultiple(&ringBuffer, ringBufferCapacity(), 0, 2);
    assert(nValuePushed == ringBufferCapacity());
    assert(ringBufferFull(&ringBuffer));
  }
  {
    // Removing a single value, the buffer should no longer be full.
    uint8_t value = 0;
    const bool success = ringBufferPop(&ringBuffer, &value);
    assert(success);
    assert(!ringBufferFull(&ringBuffer));
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRingBufferPeek() {
  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  const uint8_t expectedValue = 42;

  {
    // Given an empty buffer, peek must return false
    uint8_t value = expectedValue;
    const bool success = ringBufferPeek(&ringBuffer, &value);
    assert(!success);
    // Again, the passed value is expected to remain unmodified.
    assert(value == expectedValue);
  }
  {
    // When we peek a value, it must remain in the buffer and the size must be
    // unchanged First, push a few values
    const uint8_t nValue = 5;
    const uint8_t firstValue = expectedValue;

    pushMultiple(&ringBuffer, nValue, firstValue, 1);
    assert(ringBufferSize(&ringBuffer) == nValue);

    // The value may be "peeked"  a few times, the value itself and the buffer
    // size must remain unchanged.
    const uint8_t peekSeveralTimes = 4;
    for (uint8_t i = 0; i < peekSeveralTimes; ++i) {
      uint8_t value = 0;
      bool success = ringBufferPeek(&ringBuffer, &value);
      assert(success);
      assert(value == expectedValue);
      assert(ringBufferSize(&ringBuffer) == nValue);
    }
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

void testRunInCircles() {
  // This test checks the correct wrapping of the internal buffer read and write
  // positions

  RingBuffer ringBuffer;
  ringBufferInit(&ringBuffer);

  const uint8_t nValueMax = ringBufferCapacity();

  for (uint8_t nValue = 1; nValue <= nValueMax; ++nValue) {

    const uint32_t nRun = ((ringBufferCapacity() + 1) * 100) / nValue;

    for (uint32_t i = 0; i < nRun; ++i) {
      // Pushing multiple values and removing them again ...
      const uint16_t nValuePushed = pushMultiple(&ringBuffer, nValue, 1, 50);
      assert(nValuePushed == nValue);

      const uint16_t nValueMatch = popMultiple(&ringBuffer, nValue, 1, 50);
      assert(nValueMatch == nValue);
    }
  }
  printf("%s: passed\n", __PRETTY_FUNCTION__);
}

int main() {
  testRingBufferCapacity();

  testRingBufferPushPopSingle();
  testRingBufferPushPopMultiple();
  testRingBufferPushBeyond();
  testRingBufferPopEmpty();

  testRingBufferSize();
  testRingBufferEmpty();
  testRingBufferFull();

  testRingBufferPeek();

  testRunInCircles();
}
