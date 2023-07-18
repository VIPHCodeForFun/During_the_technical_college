/*
 * my_pwm_test.c
 *
 * Created: 17.11.2022 21:47:05
 *  Author: grubs
 */ 

/*
 * my_timer_test.c
 *
 * Created: 17.11.2022 20:25:14
 *  Author: grubs
 */ 

#include "avrhal/time.h"
#include "avrhal/usart.h"
#include "avrhal/usart-string.h"
#include "avrhal/pin.h"

int main()
{
	DDRD = 0xff;
	pinMode(31, OUTPUT);
	digitalWrite(31, 0);
	
	int pwm = 0;
	while(1)
	{
		pwmWrite(31, pwm);
		pwm++;
		
		pwm = pwm % 255;
		_delay_ms(100);

	}
	return 0;
}