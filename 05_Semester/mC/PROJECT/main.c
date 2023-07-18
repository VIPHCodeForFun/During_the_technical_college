/*
 * my_test.c
 * Created: 01.11.2022
 * Author: M.Gruber P.Vidmar
 * F_CPU 8000000UL
 */

#include <avr/io.h>
#include <util/delay.h>


int main(void) {
  /* Replace with your application code */

  DDRA = 0xFF;

  while (1) {
    PORTA = ~PORTA;
    _delay_ms(1000);
  }
  return 0;
}
