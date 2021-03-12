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
#include <stdio.h>


int main(void)
{
	UART uart;
	uart.init();	
	PN532 pn;
	MANAGEMENT::cUID uid;
// 	EEPROM_WAIT
// 	eeprom_write_block(&uid, (void*)ADMIN_ADD, UID_LEN);
	MANAGEMENT mng;
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uid[i] = i*10;
	}
	mng.addCard(&uid);
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uid[i] = i*10+1;
	}
	mng.addCard(&uid);
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uid[i] = i*10+i;
	}
	mng.addCard(&uid);
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uid[i] = i*10+2*i;
	}
	mng.addCard(&uid);
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uid[i] = i*10+1;
	}
	mng.removeCard(&uid);
	
	MANAGEMENT::cUID *c = mng.getAdmin();
	
	for(uint8_t i = 0; i < UID_LEN; i++) {
		uart.send((*c)[i]);
	}
	uart.send("\n\r");

	uart.send(eeprom_read_byte((uint8_t*)COUNT_ADD));
	uart.send("\n\r");
	for(uint8_t i = 1; i < 129; i++) {
		if(!((i-1)%8)) {
			uart.send("\n\r");
		}
		uart.send(eeprom_read_byte((uint8_t*)i));
		uart.send("-");
		
	}
	while(1);
}

