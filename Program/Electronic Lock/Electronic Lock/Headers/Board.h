/*
 * Board.h
 *
 * Created: 21. 2. 2021 14:06:37
 *  Author: Michal Kubascik
 */ 

//#include "avr/delay.h"
#include <avr/io.h>

#ifndef BOARD_H_
#define BOARD_H_

#ifndef F_CPU
#define F_CPU 12000000UL
#endif

//#define SCL_CLK 20000L						//je to nutne ?  
//#define BITRATE ((F_CPU/SCL_CLK)-16)/2		//co to robi ? pri I2C ? spytat sa Miceka

#define sbi(x,y) x |= (1<<y)	//set bit
#define cbi(x,y) x &= ~(1<<y)   //clear bit
#define tbi(x,y) x ^= _BV(y)    //zmen bit

#define IRQ_PIN PORTB0			//IRQ signal of PN532 module

#define LED_R PORTC2			//Red RGB pin
#define LED_G PORTC1			//Green RGB pin
#define LED_B PORTC0			//Blue RGB pin

#define SDA_PIN PORTC4			//Serial data pin for I2C communication
#define SCL_PIN PORTC5			//Serial clock in for I2C communication

#define LOCK_PIN PORTD2			//Lock pin - output(1 - lock is open, 0 - lock is closed)

#define UBRR_VALUE 9600			//Baudrate for UART communication with PN532



#endif /* BOARD_H_ */