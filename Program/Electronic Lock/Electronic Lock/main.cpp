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
	//pn.getFirmwareVersion();
	pn.setPassiveActivationRetries(0xFF);
	int8_t ret = pn.setSAMConfig();
	if(ret) {
		printf("sam config done\n");
	} else {
		printf("Something goes wrong\n %d", ret);
	}
	while(1) {
		bool succes;
		MANAGEMENT::cUID uid = {0,0,0,0,0,0,0};
		uint8_t uidLength;
		printf("before reading card\n");
		succes = pn.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
		if(succes) {
			printf("well done boy\n");
			
			printf("%d\n", uidLength);
			for(uint8_t i = 0; i < uidLength; i++) {
				printf("%04X ", uid[i]);
			}
			} else {
			printf("no card jet\n");
		}
		_delay_ms(1000);
	}
}

