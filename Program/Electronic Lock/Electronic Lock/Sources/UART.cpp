/* 
* UART.cpp
*
* Created: 21. 2. 2021 14:44:04
* Author: Michal Kubascik
*/


#include "../Headers/UART.h"

// default constructor
UART::UART(){
	PRR &= ~(1<<PRUSART0);
	this->init();
} //UART

// default destructor
UART::~UART(){
	PRR |= (1<<PRUSART0);
} //~UART
void UART::init(void)
{
	DDRD |=(1<<PORTD1);					// Tx output
	DDRD &=~(1<<PORTD0);				// Rx input
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);	// BAUDERATE
	UBRR0L = (uint8_t)UBRR_VALUE;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);  //8 bits, parit non, 1 stop
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	// enable rx a tx
	UCSR0A |= (1<<U2X0);
};

void UART::sendChar(uint8_t x)
{
	while(!(UCSR0A& (1<<UDRE0))){};    // caka na uvolnenie UDR
	UDR0 = x;
};

uint8_t UART::recieveChar(void)
{
	while(!(UCSR0A& (1<<RXC0))){};  //return '0';  // pozor uprava: necaka na prijem
	return UDR0;
};


uint8_t UART::recieveChar(uint8_t timeout)
{
	while(!(UCSR0A& (1<<RXC0))){}; 
	return UDR0;
}

void UART::sendBytes(uint8_t* data, const uint8_t len)
{
	for(uint8_t i=0; i < len; i++) this->sendChar(*(data++));
};

void UART::send( const char* data) {
	for ( const char* s = data; *s; ++s) {
		this->sendChar( *s);
	}
};

void UART::send( long num) {
	if ( num < 0) {
		this->sendChar( '-');
		num = -num;
	}
	this->send( ( unsigned long) num);
};

void UART::send( unsigned long num) {
	// max pocet signed/unsigned long je 10
	char digits[10];
	uint8_t len = 0;
	do {
		digits[len] = '0' + ( num % 10);
		len++;
	} while ( num /= 10);
	while ( len > 0) {
		this->sendChar( digits[--len]);
	}
};

void UART::send( int num) {
	this->send((long) num);
};

void UART::send( unsigned int num) {
	this->send(( unsigned long) num);
};

