/* 
* ATWIN.cpp
*
* Created: 21. 2. 2021 14:41:08
* Author: Michal Kubascik
*/


#include "../Headers/ATWIN.h"

// default constructor
ATWIN::ATWIN()
{
} //ATWIN

 ATWIN::ATWIN(I2C pI2C)
 {
	this->i2c = pI2C;
 }

// default destructor
ATWIN::~ATWIN()
{
} //~ATWIN
