/*
* Electronic Lock.cpp
*
* Created: 21. 2. 2021 14:05:53
* Author : Michal Kubascik
*/

#include "Headers/ATWIN.h"
#include "Headers/Board.h"
#include "Headers/EEPROM.h"
#include "Headers/LED.h"
#include "Headers/Lock.h"
#include "Headers/PN532.h"
#include <stdio.h>


int main(void)
{
	I2C i2c;
	UART uart;
	
	i2c.test();
	while (1){
	}
}

