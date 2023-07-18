/*
 * my_test.c
 *
 * Created: 27.10.2022 21:21:40
 *  Author: M.Gruber P.Vidmar
 */
#include "avrhal/usart-string.h"
#include "avrhal/usart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define LOOP_DELAY_MS 2000

int main(void)
{

    usartSetup(USART_B9600, USART_CONFIG_8N1);

    sei(); // Enable interrupts

while(1)
{
    usartStringPrintln(" ");
    // 1 Test LB 2.2.2
    usartWrite('I');

    // 2 Test LB 2.2.2
    usartStringWrite(" love deadlines.");

    // 3 Test LB 2.2.2
    usartStringPrint("I %s the %s noise", "love", "whooshing");

    // 4 Test LB 2.2.2
    usartStringPrintln(" they %s as they %s by.", "make", "go");
    usartStringPrintln(" - Douglas Adams, The Salmon of Doubt");

    // The delay is needed so that the main does not end
    _delay_ms(LOOP_DELAY_MS);
}
    return 0;
}
