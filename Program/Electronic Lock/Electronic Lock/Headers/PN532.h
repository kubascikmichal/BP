/* 
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
* based on Adafruit PN532 
*/


#ifndef __PN532_H__
#define __PN532_H__

//#include "I2C.h"
#include "UART.h"
#include "Commands.h"
class PN532
{
//variables
public:
protected:
private:
	 //I2C i2c;
	 UART u;				
	 uint8_t command;
	 
//functions
public:
	PN532();
	~PN532();
	
	bool wakeup();
	
/*	inline void initI2C(I2C i2c) {this->i2c = i2c;}*/
	inline void initUart(UART u) {this->u = u};
	bool readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout);
	uint8_t setSAMConfig();
	uint32_t getFirmwareVersion();
protected:
private:
	
	uint8_t writeData(uint8_t* data, uint8_t dataLength);
		
				
}; //PN532

#endif //__PN532_H__
