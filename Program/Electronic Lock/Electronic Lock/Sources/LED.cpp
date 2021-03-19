/* 
* LED.cpp
*
* Created: 21. 2. 2021 14:07:42
* Author: Michal Kubascik
*/


#include "../Headers/LED.h"

// default constructor
LED::LED(){
	sbi(DDRC, LED_R);
	sbi(DDRC, LED_G);
	sbi(DDRC, LED_B);
} //LED

// default destructor
LED::~LED()
{
} //~LED

void LED::light(bool r, bool g, bool b, uint8_t time){
	(!r) ? cbi(PORTC, LED_R) : sbi(PORTC, LED_R);
	(!g) ? cbi(PORTC, LED_G) : sbi(PORTC, LED_G);
	(!b) ? cbi(PORTC, LED_B) : sbi(PORTC, LED_B);
	
	for (int i = 0; i < time; i++)
	{
		_delay_ms(1000);
	}
	
	cbi(PORTC, LED_R);
	cbi(PORTC, LED_G);
	cbi(PORTC, LED_B);
}
