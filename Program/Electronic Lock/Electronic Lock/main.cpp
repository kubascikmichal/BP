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
	UART uart;
	uart.init();	
	PN532 pn;
	SoftUART s;
	s.send("\nTrolololo\n\r");
	s.send("Program na PN532 komunikaciu \n\r");

}

