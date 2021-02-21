/* 
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#ifndef __PN532_H__
#define __PN532_H__

//defining all comands

#include "Board.h"

class PN532
{
//variables
public:
protected:
private:

//functions
public:
	PN532();
	~PN532();
protected:
private:

	 uint8_t mode;			//defines, what mode will be used - I2C, SPI or UART

}; //PN532

#endif //__PN532_H__
