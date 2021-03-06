/* 
* I2C.h
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
* based on: https://github.com/Sovichea/avr-i2c-library
*/


#ifndef __I2C_H__
#define __I2C_H__

#include "Board.h"

#include <avr/io.h>
#include <util/twi.h>
#include <stdbool.h>

#define SLA_W_ADD(ADDR)		((ADDR << 1) | TW_WRITE)
#define SLA_R_ADD(ADDR)		((ADDR << 1) | TW_READ)
#define ACK		1
#define NACK	0

#define F_SCL 400000UL // SCL frequency
#define Prescaler 1 // TWPS0 = TWPS1 = 0x0
#define TWBR_val ( ( (F_CPU / F_SCL) - 16 ) / (Prescaler * 2) )

typedef enum {
	freq_400K
} i2c_freq_mode_t;

class I2C
{
//variables
public:
protected:
private:

//functions
public:
	I2C();
	~I2C();
	
	void init();
	uint16_t master_transmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, bool repeat_start);
	uint16_t master_receive(uint8_t slave_addr, uint8_t* p_data, uint8_t len);
	uint8_t test();
	
protected:
private:
	uint16_t start();
	uint16_t stop();
	uint16_t write_sla(uint8_t slaveAddress);
	uint16_t write(uint8_t data);
	uint16_t read(bool read_ack);
	
}; //I2C

#endif //__I2C_H__
