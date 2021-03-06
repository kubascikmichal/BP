/* 
* LED.h
*
* Created: 21. 2. 2021 14:07:42
* Author: Michal Kubascik
*/


#ifndef __LED_H__
#define __LED_H__

#include "Board.h"

class LED
{
//variables
public:
protected:
private:

//functions
public:
	LED();
	~LED();
	
	void light(bool r, bool g, bool b, uint8_t time);
protected:
private:

}; //LED

#endif //__LED_H__
