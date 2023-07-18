#include "avrhal/usart-string.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

uint8_t usartStringWrite(const char* str)
{
    char* ptrStr = (char*)str;
    uint8_t count = 0;
    while (*ptrStr != '\0') {
        usartWrite(*ptrStr);
        ptrStr++;
        count++;
    }
    return count;
}

uint8_t usartStringPrint(const char* format, ...)
{

    va_list ArgPtr; // List of Arguments given to the function (...)
    char buffer[usartAvailableForWrite()]; // Buffer where the builded String gets stored before sending.

    va_start(ArgPtr, format); // Set the Argumentpointer to the first argument given.
    uint8_t bufferLen = vsnprintf(buffer, usartAvailableForWrite(), format, ArgPtr); // Build the string with the given Argumentlist to the prepared Buffer.
    va_end(ArgPtr); // Free the Arguments list (not needed anymore)

    if (bufferLen > 0 && bufferLen < usartAvailableForWrite()) // Check if the builded String is now not too long or empty;
    {
        usartStringWrite(buffer);
        return bufferLen;
    } else {
        return 0;
    }
}

uint8_t usartStringPrintln(const char* format, ...) // same logic as usartStringPrint(const char *format, ...)
{

    va_list ArgPtr;
    char buffer[usartAvailableForWrite()];

    va_start(ArgPtr, format);
    uint8_t bufferLen = vsnprintf(buffer, usartAvailableForWrite(), format, ArgPtr);
    va_end(ArgPtr);

    char* lineTerminator = "\r\n"; // add lineTerminator to the function

    if (bufferLen > 0 && bufferLen < (usartAvailableForWrite() - strlen(lineTerminator))) {
        usartStringWrite(buffer);
        usartStringWrite(lineTerminator);
        return bufferLen + strlen(lineTerminator);
    } else {
        usartStringWrite(lineTerminator);
        return strlen(lineTerminator);
    }
}
