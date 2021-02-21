/* 
* PN532.cpp
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#include "../Headers/PN532.h"

// default constructor
PN532::PN532()
{
	this->mode = Mode::ALL_MODES_POSSIBLE;
} //PN532

 PN532::PN532(UART pUART)
 {
	//this->i2c = 0;
	this->uart = pUART;
	this->mode = Mode::UART_MODE;
 }

 PN532::PN532(I2C pI2C)
 {
	//this->uart = 0;
	this->i2c = pI2C;
	this->mode = Mode::I2C_MODE;
 }

// default destructor
PN532::~PN532()
{
	
} //~PN532
