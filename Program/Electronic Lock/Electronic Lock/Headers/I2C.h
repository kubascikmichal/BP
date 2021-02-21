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
	
	void init();
	
protected:
private:

}; //I2C

#endif //__I2C_H__
