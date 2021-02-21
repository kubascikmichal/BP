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
	this->i2c = new I2C(SDA_PIN, SCL_PIN);
	this->uart = new UART();
} //PN532

 PN532::PN532(UART* pUART)
 {
	this->i2c = nullptr;
	this->uart = pUART;
	this->mode = Mode.UART;
 }

 PN532::PN532(I2C* pI2C)
 {
	this->uart = nullptr;
	this->i2c = pI2C;
	this->mode = Mode.I2C;
 }

// default destructor
PN532::~PN532()
{
	if(this->i2c) {
		delete this->i2c;
	}
	if(this->uart) {
		delete this->i2c;
	}
} //~PN532
