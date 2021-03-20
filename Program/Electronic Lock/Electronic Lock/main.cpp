/*
* Electronic Lock.cpp
*
* Created: 21. 2. 2021 14:05:53
* Author : Michal Kubascik
*/

#include "Headers/Board.h"
#include "Headers/ATWIN.h"
#include "Headers/Management.h"
#include "Headers/LED.h"
#include "Headers/Lock.h"
#include "Headers/PN532.h"
#include "Headers/UART.h"
#include "Headers/SoftUART.h"


int main(void)
{
	SoftUART s;
	printf("Hello\n");
	DDRD = 1<<PORTD2;
	cbi(PORTD, PORTD2);
	_delay_ms(1000);
	sbi(PORTD, PORTD2);
	_delay_ms(1000);
	UART uart;
	PN532 pn;
	pn.start();
	if(pn.getFirmwareVersion() != 0) {
		
	}
}

