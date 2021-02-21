/* 
* ATWIN.h
*
* Created: 21. 2. 2021 14:41:08
* Author: Michal Kubascik
*/


#ifndef __ATWIN_H__
#define __ATWIN_H__

#include "Board.h"
#include "Commands.h"
#include "I2C.h"

class ATWIN
{
//variables
public:
protected:
private:
	I2C i2c;
	
//functions
public:
	ATWIN();
	~ATWIN();
	
	ATWIN(I2C pI2C);
protected:
private:

}; //ATWIN

#endif //__ATWIN_H__
