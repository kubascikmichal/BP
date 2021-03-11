/* 
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
* based on Adafruit PN532 
*/


#ifndef __PN532_H__
#define __PN532_H__

#include "I2C.h"
#include "Commands.h"
class PN532
{
//variables
public:
protected:
private:
	 I2C i2c;				//object of I2C for communication via I2C bus
	uint8_t pn532_packetbuffer[64] = {0};
//functions
public:
	PN532();
	~PN532();
	
	inline void initI2C(I2C i2c) {this->i2c = i2c;}
	bool readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout);
	uint8_t setSAMConfig();
	uint32_t getFirmwareVersion();
	uint8_t writeData(uint8_t* data, uint8_t dataLength);
protected:
private:
		
				
}; //PN532

#endif //__PN532_H__
