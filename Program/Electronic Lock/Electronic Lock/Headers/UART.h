/* 
* UART.h
*
* Created: 21. 2. 2021 14:44:04
* Author: Michal Kubascik
*/


#ifndef __UART_H__
#define __UART_H__

#include "Board.h"

class UART
{
//variables
public:
protected:
private:

//functions
public:
	UART();
	~UART();
	
	void init(void);

	void sendChar(uint8_t x);
	uint8_t recieveChar(void);
	uint8_t recieveChar(uint8_t timeout);

	void sendBytes(uint8_t* data, const uint8_t len);
	void send( const char* data);
	void send( long num);
	void send( unsigned long num);
	void send( int num);
	void send( unsigned int num);
protected:
private:

}; //UART

#endif //__UART_H__
