/* 
* I2C.cpp
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
*/


#include "../Headers/I2C.h"

// default constructor
I2C::I2C()
{
} //I2C

 I2C::I2C(int sda, int scl) {
	this->sda = sda;
	this->scl = scl;
 }

// default destructor
I2C::~I2C()
{
} //~I2C
