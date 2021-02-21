/* 
* I2C.h
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
*/


#ifndef __I2C_H__
#define __I2C_H__

#include "Board.h"

class I2C
{
//variables
public:
protected:
private:
	int sda;
	int scl;

//functions
public:
	I2C();
	~I2C();
	
	void init(bool mode); //0 for input, 1 for output ?? is it important?
	void write(uint8_t param);
	uint8_t read();
	
protected:
private:
	void initRead();
	void initWrite();
	void writeStart();
	void writeStop();
	void writeBit(bool p);
	bool getMode();
	bool setMode(bool mode);

}; //I2C

#endif //__I2C_H__
