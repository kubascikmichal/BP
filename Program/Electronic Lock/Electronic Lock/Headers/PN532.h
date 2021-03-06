/* 
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#ifndef __PN532_H__
#define __PN532_H__

#include "UART.h"
#include "I2C.h"
#include "Commands.h"
#include "Modes.h"

class PN532
{
//variables
public:
protected:
private:
	 I2C i2c;				//object of I2C for communication via I2C bus
//functions
public:
	PN532();
	~PN532();
	
	inline void initI2C(I2C i2c) {this->i2c = i2c;}
	
protected:
private:
	uint8_t writeCommand(const uint8_t *header, uint8_t hlen, const uint8_t *body = 0, uint8_t blen = 0);
	int16_t readResponse(uint8_t buf[], uint8_t len, uint16_t timeout);
// 	
// 	inline void uint8_t write(uint8_t data) { this->i2c.write(data); }
// 	inline uint8_t read() { this->i2c.receive(); }
		
				
}; //PN532

#endif //__PN532_H__
