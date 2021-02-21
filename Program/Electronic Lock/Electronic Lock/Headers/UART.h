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
	
	void Uart_init(void);

	void Uart_send_char(uint8_t x);
	uint8_t Uart_rec_char(void);

	void Uart_send_bytes(char* data, const uint8_t len);
	void Uart_send( const char* data);
	void Uart_send( long num);
	void Uart_send( unsigned long num);
	void Uart_send( int num);
	void Uart_send( unsigned int num);
protected:
private:

}; //UART

#endif //__UART_H__
