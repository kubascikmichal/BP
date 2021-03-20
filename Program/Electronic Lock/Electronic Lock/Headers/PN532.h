/*
* PN532.h
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
* based on Adafruit PN532
*/


#ifndef __PN532_H__
#define __PN532_H__

#define PN532_HSU_READ_TIMEOUT 1000
#define PN532_ACK_WAIT_TIME           10  // ms, timeout of waiting for ACK

#define PN532_INVALID_ACK             -1
#define PN532_TIMEOUT                 -2
#define PN532_INVALID_FRAME           -3
#define PN532_NO_SPACE                -4
#include "UART.h"
#include "Commands.h"
class PN532
{
	//variables
	public:
	protected:
	private:
	//I2C i2c;
	UART u;
	uint8_t command;
	uint8_t pn532_packetbuffer[64];
	
	//functions
	public:
	PN532();
	~PN532();
	
	bool begin(uint8_t baudrate);
	bool start();
	bool wakeup();
	inline void initUart(UART u) {this->u = u;}
	bool readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout);
	uint8_t setSAMConfig();
	uint32_t getFirmwareVersion();
	protected:
	private:
	
	uint8_t writeCommand( uint8_t *header, uint8_t hlen,  uint8_t *body = 0, uint8_t blen = 0);
	uint16_t readResponse(uint8_t buf[], uint8_t len, uint16_t timeout = PN532_HSU_READ_TIMEOUT);
	
	int8_t receive(uint8_t *buf, int len, uint16_t timeout=1000);
	int8_t readAckFrame();
}; //PN532

#endif //__PN532_H__
