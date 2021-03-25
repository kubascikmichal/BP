/* 
* SoftUART.h
*
* Created: 6.11.2020 18:36:50
* Author: Dominik
*/


#ifndef __SOFTUART_H__
#define __SOFTUART_H__

#define BUFFER_SIZE 255

#include "Board.h"

class SoftUART
{
//variables
public:
protected:
private:
	FILE *uart_ptr;

//functions
public:
	SoftUART();
	~SoftUART();
	static int sendByte(char data, FILE *stream);
	static int receiveByte(FILE *stream);
	void send(const char* word);
	char* receive(char* buffer);
protected:
private:
	SoftUART( const SoftUART &c );
	SoftUART& operator=( const SoftUART &c );
	static void sendByteS(uint8_t data);
	static uint8_t receiveByteS(void);

}; //SoftUART

#endif //__SOFTUART_H__
