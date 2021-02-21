/* 
* I2C.cpp
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
*/


#include "../Headers/I2C.h"

// default constructor
I2C::I2C(){
	this->sda = SDA_PIN;
	this->scl = SCL_PIN;
} //I2C

// default destructor
I2C::~I2C(){

} //~I2C
 
void I2C::init(){
	
}


