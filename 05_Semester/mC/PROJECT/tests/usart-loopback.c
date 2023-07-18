#include "avrhal/pin.h"
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include "utils/bit.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TEST_BUF_LEN 255
#define USART_MIN_INTERNAL_BUFFER 127
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

/** Helper function: Used in all usartWrite* tests to check whether the sent
 * data matches.the expectations.
 * @param[in] expectedResult the data which is expected on the usart RX line
 * @param[in] expectedLen the length of \p expectedResult
 * @return True if the test passed, false otherwise
 */
bool checkResult(const char *expectedResult, const uint16_t expectedLen) {
  _delay_ms(500); // Wait for all TX/RX on the usart line to finish

  bool success = true;
  uint8_t result[TEST_BUF_LEN] = {0};

  success &= (usartAvailableForRead() == expectedLen);
  const uint8_t nRead = usartReadBytes(result, TEST_BUF_LEN);
  success &= (nRead == expectedLen);
  success &= (strncmp(expectedResult, (const char *)result, expectedLen) == 0);
  return success;
}

/** Helper function: Launched inbetween each test, to clear any remaining
 * incoming usart data.
 * @note When all tests pass. there should not be any remaining data to be
 * cleared.
 */
void clearReceivedUsartData() {
  uint8_t value;
  bool success = true;
  while (success) {
    success = usartRead(&value);
  }
}

/** Test if the internal avrhal/usart buffer provides sufficient space to run
 * all tests.
 * @note See \p USART_MIN_INTERNAL_BUFFER
 * @return True if the test passed, false otherwise
 */
bool testUsartAvailable() {
  bool success = true;
  success &= (usartAvailableForRead() == 0);
  success &= (usartAvailableForWrite() >= USART_MIN_INTERNAL_BUFFER);
  return success;
}

/** Basic test: Write 2 characters and read 2 character again. The characters
 * must match.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartWriteRead() {
  bool success = true;

  success &= usartWrite('I');
  success &= usartWrite('O');
  _delay_ms(100); // Anather small wait, to ensure all I/O on the usart line has
                  // finished
  success &= (usartAvailableForRead() == 2);
  uint8_t value = 0;
  success &= usartRead(&value);
  success &= (value == 'I');
  success &= usartRead(&value);
  success &= (value == 'O');
  return success;
}

/** Test if usartReadbytes() behaves nicely when usart data is available while
 * the provided buffer has zero space left.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartReadBytesZeroSpace() {
  bool success = true;

  success &= usartWrite('4');
  _delay_ms(100); // Wait for all TX/RX on the usart line to finish
  success &= (usartAvailableForRead() == 1);
  uint8_t buffer[10] = {0};
  const uint8_t remainingSpaceInBuffer = 0;
  const uint8_t nRead = usartReadBytes(buffer, remainingSpaceInBuffer);
  success &= (nRead == remainingSpaceInBuffer);
  success &= (usartAvailableForRead() == 1);
  return success;
}

/** Writing a normal zero-terminated string and reading it again.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartStringWrite() {
  bool success = true;
  const char *expectedResult =
      "\r\nThe Moon is essentially gray - no color.\r\n";
  const uint8_t len = strlen(expectedResult);

  const uint8_t nWritten = usartStringWrite(expectedResult);
  success &= (nWritten == len);
  success &= checkResult(expectedResult, len);
  return success;
}

/** Writing a formatted string and reading it again.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartStringPrint() {
  bool success = true;
  const char *expectedResult =
      "Little wonder that our star, the sun, "
      "has been the focal point of scientific investigation for centuries.\r\n";
  const uint8_t len = strlen(expectedResult);
  const uint8_t nWritten =
      usartStringPrint("Little wonder that our star, %s, has been the %s of "
                       "scientific investigation for %s",
                       "the sun", "focal point", "centuries.\r\n");
  success &= (nWritten == len);
  success &= checkResult(expectedResult, len);
  return success;
}

/** Writing a formatted string and reading it again.
 * The read string is expected to have a trailing \r\n sequence appended.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartStringPrintln() {
  bool success = true;
  const char *expectedResult = "Better to light one candle than to curse the "
                               "darkness. - Chinese Proverb\r\n";
  const uint8_t len = strlen(expectedResult);
  const uint8_t nWritten =
      usartStringPrintln("Better to light one candle than to curse the "
                         "darkness. - Chinese Proverb");
  success &= (nWritten == len);
  success &= checkResult(expectedResult, len);
  return success;
}

/** In this test the transmit buffer is getting stuffed to the limit.
 * The number of written bytes is expected to match the initial value returned
 * by usartAvailableForWrite().
 * @note To prevent the buffer from being processed by usart hardware interrupts
 * in the meantime, all interrupts are shortly disabled.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartWriteExceedBuffer() {
  bool success = true;
  const uint8_t data = (uint8_t)0xCAFEBAD40U;
  cli(); // *Freeze* the usart interface I/O by disabling all interrupts
  uint8_t expectedLen = usartAvailableForWrite();
  uint8_t nWritten = 0;
  bool writeSuccess = true;
  while (writeSuccess) {
    writeSuccess = usartWrite(data);
    nWritten += writeSuccess;
  }
  success &= (nWritten == expectedLen);
  sei();
  _delay_ms(500);
  for (uint8_t i = 0; i < nWritten; ++i) {
    uint8_t value = 0;
    success &= usartRead(&value);
    success &= (value == data);
  }
  return success;
}

/** Writing an empty string and reading it again.
 * The read string is expected to consist just of the \r\n sequence.
 * @note A loopback on the usart line is required. (Please refer to the lab
 * instructions)
 * @return True if the test passed, false otherwise
 */
bool testUsartStringPrintlnEmpty() {
  bool success = true;
  const char *expectedResult = "\r\n";
  const uint8_t nWritten = usartStringPrintln("");
  success &= (nWritten == strlen(expectedResult));
  success &= checkResult(expectedResult, nWritten);
  return success;
}

/** The reward for passing all tests :>
 */
void visualizeSuccess() {
  for (uint8_t i = 0; i < 70; ++i) {
    PORTA = (128 >> (i & 7)) | ((255 << i / 8) >> 8);
    _delay_ms(75);
  }
  PORTA = 0;
}

/** Running all specified tests
 * @return A bit field where each failed test is marked as '1'. On success the
 * value 0 is returned.
 */
uint8_t runTests() {
  typedef bool (*TestFunction)(void);

  TestFunction tests[] = {
      testUsartAvailable,          testUsartWriteRead,
      testUsartReadBytesZeroSpace, testUsartStringWrite,
      testUsartStringPrint,        testUsartStringPrintln,
      testUsartWriteExceedBuffer,  testUsartStringPrintlnEmpty};
  uint8_t result = 0;

  for (uint8_t i = 0; i < ARRAY_SIZE(tests); ++i) {
    const bool success = tests[i](); // Run the test
    if (!success) {
      BIT_SET(result, i);
    }
    clearReceivedUsartData();
  }
  return result;
}

int main() {
  DDRA = 0xFF;
  PORTA = 0;

  usartSetup(USART_B9600, USART_CONFIG_8N1);
  sei();

  while (1) {
    _delay_ms(250.0);
    const uint8_t result = runTests();
    const uint8_t failure = (result != 0);

    if (failure) {
      PORTA = result; // Show all failed tests on the LED panel.
    } else {
      visualizeSuccess();
    }
    clearReceivedUsartData();
  }

  return 0;
}
