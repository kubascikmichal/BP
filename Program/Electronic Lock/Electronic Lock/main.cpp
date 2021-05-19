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
	LED l;
	l.BLUEon();
	_delay_ms(150);
	l.BLUEoff();
	l.REDon();
	_delay_ms(150);
	l.REDoff();
	l.GREENon();
	_delay_ms(150);
	l.GREENoff();
	Lock lck;
	SoftUART s;
	printf("Hello\n");
	UART uart;
	PN532 pn;
	pn.start();
	pn.getFirmwareVersion();
	pn.setPassiveActivationRetries(0xFF);
	int8_t ret = pn.setSAMConfig();
	if(ret>=0) {
		printf("sam config done\n");
		} else {
		printf("Something goes wrong\n %d", ret);
	}
	MANAGEMENT mng;
	bool adminMode = false;
	while(1) {
		l.ALLoff();
		if(*(mng.getAdmin())[0] == 255){
			//get cyan light
			l.CYANon();
			} else {
			if(adminMode) {
				//get orange light
				l.ORANGEon();
				} else  {
				//get blue light
				l.BLUEon();
			}
		}
		bool succes;
		MANAGEMENT::cUID uid = {0,0,0,0,0,0,0};
		uint8_t uidLength;
		printf("before reading card\n");
		_delay_ms(2000);
		succes = pn.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
		if(succes) {
			printf("well done boy\n");
			printf("%d\n", uidLength);
			for(uint8_t i = 0; i < uidLength; i++) {
				printf("%02X ", uid[i]);
			}
			printf("\n-----------------------------\n");
			if(*(mng.getAdmin())[0] == 255) {
				printf("No admin set - adding admin \n\r");
				mng.addCard(&uid);
				//get blue-green-led three times blink
				l.ALLoff();
				for (int i = 0; i < 5; i++)	{
					l.BLUEon();
					_delay_ms(200);
					l.BLUEoff();
					l.GREENon();
					_delay_ms(200);
					l.GREENoff();
				}
				} else {
				printf("I have admin \n");
				uint8_t index;
				uint8_t ret = mng.matchCards(&uid, &index);
				if(ret == 1) {
					adminMode = !adminMode;
					} else {
					if(adminMode) {
						if(ret == 2) {
							printf("removing card\n");
							mng.removeCard(&uid);
							//two red-orange blink blink
							l.ALLoff();
							for (int i = 0; i < 5; i++)	{
								l.REDon();
								_delay_ms(200);
								l.REDoff();
								l.ORANGEon();
								_delay_ms(200);
								l.ORANGEoff();
							}
							} else{
							printf("adding card\n");
							mng.addCard(&uid, true);
							//two green-orange blink blink
							l.ALLoff();
							for (int i = 0; i < 5; i++)	{
								l.GREENon();
								_delay_ms(200);
								l.GREENoff();
								l.ORANGEon();
								_delay_ms(200);
								l.ORANGEoff();
							}
						}
						
						adminMode = !adminMode;
						} else {
						if(ret ==0) {
							printf("Access denied\n");
							//blinking red for 10 seconds - so 20 times probably - beside lock is closed
							l.ALLoff();
							//lock lock
							for (int i = 0; i < 15; i++)	{
								l.REDon();
								_delay_ms(300);
								l.REDoff();
								_delay_ms(300);
							}
							} else {
							printf("Access approved\n");
							//blinking red for 10 seconds - so 20 times probably - beside lock is open
							lck.unlock();
							l.ALLoff();
							for (int i = 0; i < 15; i++)	{
								l.GREENon();
								_delay_ms(300);
								l.GREENoff();
								_delay_ms(300);
							}
							lck.lock();
						}
					}
				}
				
			}
			
			} else {
			printf("no card jet\n");
		}
	}
}

