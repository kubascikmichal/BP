/* 
* LED.cpp
*
* Created: 21. 2. 2021 14:07:42
* Author: Michal Kubascik
*/


#include "../Headers/LED.h"

// default constructor
LED::LED(){
	sbi(DDRD, LED_R);
	sbi(DDRD, LED_G);
	sbi(DDRD, LED_B);
} //LED

// default destructor
LED::~LED()
{
} //~LED

void LED::light(bool r, bool g, bool b, uint8_t time){
	(r) ? cbi(PORTD, LED_R) : sbi(PORTD, LED_R);
	(g) ? cbi(PORTD, LED_G) : sbi(PORTD, LED_G);
	(b) ? cbi(PORTD, LED_B) : sbi(PORTD, LED_B);
	
	for (int i = 0; i < time; i++)
	{
		_delay_ms(100);
	}
	
	sbi(PORTD, LED_R);
	sbi(PORTD, LED_G);
	sbi(PORTD, LED_B);
}
