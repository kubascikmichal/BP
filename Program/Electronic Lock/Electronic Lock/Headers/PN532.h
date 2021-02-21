/* 
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#ifndef __PN532_H__
#define __PN532_H__

#include "Board.h"
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
	 Mode::Mode mode;			//defines, what mode will be used - I2C, SPI or UART
	 I2C i2c;				//object of I2C for communication via I2C bus
	 UART uart;	

//functions
public:
	PN532();
	~PN532();
	
	PN532(I2C pI2C);
	PN532(UART pUART);
	
protected:
private:			//object of UART for communication via UART
}; //PN532

#endif //__PN532_H__
