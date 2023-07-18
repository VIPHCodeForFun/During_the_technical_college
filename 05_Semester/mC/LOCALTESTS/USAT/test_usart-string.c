#include "usart-string.h"

#define RING_BUFFER_CAPACITY 252
#include "ring-buffer.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// Note: This test assumes all functions of usart-string module only rely on usartWrite() and optionally usartAvailableForWrite().

// The following implementation is used as a "test double" instead of the avrhal/usart module:
static RingBuffer usartTxBuffer;

bool usartWrite(uint8_t byte)
{
    return ringBufferPush(&usartTxBuffer, byte);
}

uint8_t usartAvailableForWrite()
{
    return ringBufferSize(&usartTxBuffer);
}

/** Helper function: Used in all tests to check whether the sent data matches the expected results.
 * @param[in] expectedResult  the data which is expected on the usart RX line
 * @param[in] expectedLen  the length of \p expectedResult
 * @param[in] returnVal  the returned value of the function under test
*/
void checkResult(const char* testName, const char* expectedResult, uint16_t expectedLen, uint16_t returnVal)
{
    printf("%s:\n", testName);

    // The return value of the function under test needs to match the ringbuffer size
    assert(ringBufferSize(&usartTxBuffer) == returnVal);

    // Compare the ringbuffer content with the expected string.
    for (uint16_t i = 0; i < expectedLen; ++i) {
        uint8_t val;
        assert(ringBufferPop(&usartTxBuffer, &val));
        assert(val == expectedResult[i]);
    }

    // The return value of the function under test needs to match the expected string length.
    assert(expectedLen == returnVal);

    printf("  passed\n");
}

/** Writing a normal zero-terminated string.
*/
void testUsartStringWrite()
{
    // Test string source: https://github.com/subsurface/subsurface#contributing
    const char* expectedResult = "\r\nHeader line: explain the commit in one line (use the imperative)\r\n";
    const uint8_t expectedLen = strlen(expectedResult);
    const uint8_t returnVal = usartStringWrite(expectedResult);

    checkResult(__PRETTY_FUNCTION__, expectedResult, expectedLen, returnVal);
}

/** Writing a formatted string.
*/
void testUsartStringPrint()
{
    // Test string source: https://github.com/subsurface/subsurface#contributing
    const char* expectedResult = "Please use verbs in the imperative in the commit message,"
                                 " as in \"Fix bug that...\", \"Add file/feature ...\","
                                 " or \"Make Subsurface...\"\r\n";

    const uint8_t expectedLen = strlen(expectedResult);
    const uint8_t returnVal = usartStringPrint("Please use verbs in the imperative "
                                               "in the commit message, as in "
                                               "\"%s\", \"%s\", or \"%s\"\r\n",
        "Fix bug that...", "Add file/feature ...", "Make Subsurface...");
    checkResult(__PRETTY_FUNCTION__, expectedResult, expectedLen, returnVal);
}

/** Writing a formatted string.
 * The written string is expected to have a trailing \r\n sequence appended.
*/
void testUsartStringPrintln()
{
    // Test string source: https://github.com/subsurface/subsurface#contributing
    const char* expectedResult = "Make sure you explain your solution and "
                                 "why you're doing what you're doing, as opposed"
                                 " to describing what you're doing.\r\n";
    const uint8_t expectedLen = strlen(expectedResult);
    const uint8_t returnVal = usartStringPrintln("Make sure you explain your solution and "
                                                 "why you're doing what you're doing, as opposed"
                                                 " to describing what you're doing.");

    checkResult(__PRETTY_FUNCTION__, expectedResult, expectedLen, returnVal);
}

/** Writing an empty string.
 * The written string is expected to consist of the \r\n sequence.
*/
void testUsartStringPrintlnEmpty()
{
    const char* expectedResult = "\r\n";
    const uint8_t expectedLen = strlen(expectedResult);
    const uint8_t returnVal = usartStringPrintln("");
    checkResult(__PRETTY_FUNCTION__, expectedResult, expectedLen, returnVal);
}

/** Run all specified tests
*/
void runTests()
{
    typedef void (*TestFunction)(void);

    TestFunction tests[] = {
        testUsartStringWrite, testUsartStringPrint,
        testUsartStringPrintln, testUsartStringPrintlnEmpty
    };

    for (uint8_t i = 0; i < ARRAY_SIZE(tests); ++i) {
        ringBufferInit(&usartTxBuffer);
        tests[i](); // Run the test
    }
}

int main()
{
    runTests();
    return 0;
}
