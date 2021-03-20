/*
 * Board.h
 *
 * Created: 21. 2. 2021 14:06:37
 *  Author: Michal Kubascik
 */ 

//#include "avr/delay.h"
//#define F_CPU
#define F_CPU 12000000UL
//#endif
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#define DEBG 1

#ifndef BOARD_H_
#define BOARD_H_




#define sbi(x,y) x |= (1<<y)	//set bit
#define cbi(x,y) x &= ~(1<<y)   //clear bit
#define tbi(x,y) x ^= _BV(y)    //zmen bit

#define IRQ_PIN PORTB0			//IRQ signal of PN532 module

#define LED_B PORTC2			//Red RGB pin
#define LED_G PORTC1			//Green RGB pin
#define LED_R PORTC0			//Blue RGB pin

#define S_TX PORTC4
#define S_RX PORTC5

#define S_BAUD 9600

#define SDA_PIN PORTC4			//Serial data pin for I2C communication
#define SCL_PIN PORTC5			//Serial clock in for I2C communication

#define LOCK_PIN PORTD2			//Lock pin - output(1 - lock is open, 0 - lock is closed)

#define TXD PORTD1
#define RXD PORTD0
#define BAUDERATE	115200  //115200	//1200
#define UBRR_VALUE ((F_CPU / (BAUDERATE * 8L)) -1)

#endif /* BOARD_H_ */