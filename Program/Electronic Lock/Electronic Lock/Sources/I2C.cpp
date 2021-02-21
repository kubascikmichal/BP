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

void I2C::init(bool mode){
	 
}

void I2C::initRead(){
	// set pull up resistors to input
}

void I2C::initWrite(){
	// set pull up resistors to output
}

void I2C::writeStart(){
	//set sda 0, scl 1, sda 1 
}

void I2C::writeStop(){
	//set sda 1, scl 1, sda 0 
}

void I2C::writeBit(bool p){
	//set scl 0, sda p, scl 1, scl 0
	//delay between messages - slave must be able to read it
}

void I2C::write(uint8_t param) {
	//call writeBit
}

uint8_t I2C::read(){
	//don't know what to do here
}

bool I2C::getMode(){
	return (DDRC&(1<<SDA_PIN));
}

bool I2C::setMode(bool mode){
	mode ? sbi(DDRC, SDA_PIN) : cbi(DDRC, SDA_PIN);
	//mode ? sbi(DDRC, SCL_PIN) : cbi(DDRC, SCL_PIN);
}

