/*
* I2C.cpp
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
*/


#include "../Headers/I2C.h"

I2C::I2C() {
	init();
	DDRC &= ~(1 << SDA_PIN);
	DDRC &= ~(1 << SCL_PIN);
	PORTC &= ~(1 << SCL_PIN);
	PORTC &= ~(1 << SDA_PIN);
}

I2C::~I2C() {

}

void I2C::init(){
	// atmel Datasheet p232
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
	// atmel Datasheet p212
	TWBR = (uint8_t)TWBR_val;
}

uint16_t I2C::master_transmit(uint8_t slave_addr, uint8_t* p_data, uint8_t len, bool repeat_start){
	uint16_t error_code;
	
	/* Send START condition */
	error_code = start();
	if (error_code)
	{
		return error_code;
	}
	
	/* Send slave address with WRITE flag */
	error_code = write_sla(SLA_W_ADD(slave_addr));
	if (error_code)
	{
		return error_code;
	}
	
	/* Send data byte in single or burst mode */
	for (int i = 0; i < len; ++i)
	{
		error_code = write(p_data[i]);
		if (error_code)
		{
			return error_code;
		}
	}
	
	if (!repeat_start)
	{
		/* Send STOP condition */
		stop();
	}
	
	return 0;
}

uint16_t I2C::master_receive(uint8_t slave_addr, uint8_t* p_data, uint8_t len){
	uint16_t error_code;

	/* Send START condition */
	error_code = start();
	if (error_code)
	{
		return error_code;
	}

	/* Write slave address with READ flag */
	error_code = write_sla(SLA_R_ADD(slave_addr));
	if (error_code)
	{
		return error_code;
	}

	/* Read single or multiple data byte and send ack */
	for (int i = 0; i < len-1; ++i)
	{
		p_data[i] = read(ACK);
	}
	p_data[len-1] = read(NACK);

	/* Send STOP condition */
	stop();

	return 0;
}

uint16_t I2C::start(){
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	// check if the start condition was successfully transmitted
	if(TW_STATUS != TW_START){
		return TW_STATUS;
	}
	return 0;
}

uint16_t I2C::stop(){
	TWCR = 0;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	return 0;
}

uint16_t I2C::write_sla(uint8_t slaveAddress){
	TWDR = slaveAddress;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1<<TWINT)));
	// 	if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK){
	// 		return TW_STATUS;
	// 	}
	return 0;
}

uint16_t I2C::write(uint8_t data){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag to set */
	while (!(TWCR & (1<<TWINT)));

	return 0;
}

uint16_t I2C::read(bool read_ack){
	if (read_ack)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_ACK)
		{
			return TW_STATUS;
		}
	}
	else
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		while (!(TWCR & (1 << TWINT)));
		if (TW_STATUS != TW_MR_DATA_NACK)
		{
			return TW_STATUS;
		}
	}
	uint8_t data = TWDR;
	return data;
}
uint8_t I2C::test() {
	start();
	write((0x48 << 1) | 1);
	stop();
	return 0;
}