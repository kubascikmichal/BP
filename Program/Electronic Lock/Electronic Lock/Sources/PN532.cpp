/*
* PN532.cpp
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#include "../Headers/PN532.h"
#include "../Headers/SoftUART.h"
SoftUART s;

// default constructor
PN532::PN532(){

} //PN532


PN532::~PN532(){
	
} //~PN532

bool PN532::setPassiveActivationRetries(uint8_t maxret){
	pn532_packetbuffer[0] = PN532_COMMAND_RFCONFIGURATION;
	pn532_packetbuffer[1] = 5;    // Config item 5 (MaxRetries)
	pn532_packetbuffer[2] = 0xFF; // MxRtyATR (default = 0xFF)
	pn532_packetbuffer[3] = 0x01; // MxRtyPSL (default = 0x01)
	pn532_packetbuffer[4] = maxret;
	
	if(writeCommand(pn532_packetbuffer, 5))
	return 0;
	
	return(0<readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer), 1000));
}

bool PN532::readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout){
	pn532_packetbuffer[0] = PN532_COMMAND_INLISTPASSIVETARGET;
	pn532_packetbuffer[1] = 1;  // max 1 cards at once (we can set this to 2 later)
	pn532_packetbuffer[2] = cardbaudrate;
	if(writeCommand(pn532_packetbuffer, 3)) {
		return 0;
	}
	
	if(readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer)) < 0) {
		return 0;
	}
	printf("stonks\n");
	if(pn532_packetbuffer[0] != 1)
	return 0;
	*uidLength = pn532_packetbuffer[5];
	for(uint8_t i = 0; i < *uidLength; i++) {
		uid[i] = pn532_packetbuffer[6 + i];
	}
	
	return 1;
}

uint8_t PN532::setSAMConfig(){		pn532_packetbuffer[0] = PN532_COMMAND_SAMCONFIGURATION;
	pn532_packetbuffer[1] = 0x01; // normal mode;
	pn532_packetbuffer[2] = 0x14; // timeout 50ms * 20 = 1 second
	pn532_packetbuffer[3] = 0x01; // use IRQ pin!

	if(writeCommand(pn532_packetbuffer, 4))
	return 0;
	
	uint8_t t = readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer));
	
	printf("I have done everything\n");
	return t;

}

uint32_t PN532::getFirmwareVersion(){	uint32_t response;
	pn532_packetbuffer[0] = PN532_COMMAND_GETFIRMWAREVERSION;
	if(writeCommand(pn532_packetbuffer, 1)){
		return 0;
	}
	int16_t status =  readResponse(pn532_packetbuffer, sizeof(pn532_packetbuffer), 1000);
	if(status < 0) {
		return 0;
	}

	response = pn532_packetbuffer[0];
	response <<=8;
	response |= pn532_packetbuffer[1];
	response <<=8;
	response |= pn532_packetbuffer[2];
	response <<=8;
	response |= pn532_packetbuffer[3];
	return response;
}

bool PN532::begin(uint8_t baudrate) {
}

bool PN532::start(){
	this->begin(BAUDERATE);
	this->wakeup();
}

bool PN532::wakeup(){
	u.sendChar(0x55);
	u.sendChar(0x55);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	u.sendChar(0);
	_delay_ms(3);
}
uint8_t PN532::writeCommand( uint8_t *header, uint8_t hlen,  uint8_t *body /*= 0*/, uint8_t blen /*= 0*/)
{


	this->command = header[0];
	
	u.sendChar(PN532_PREAMBLE);
	u.sendChar(PN532_STARTCODE1);
	u.sendChar(PN532_STARTCODE2);
	
	uint8_t length = hlen + blen + 1;   // length of data field: TFI + DATA
	u.sendChar(length);
	u.sendChar(~length + 1);         // checksum of length
	
	u.sendChar(PN532_HOSTTOPN532);
	uint8_t sum = PN532_HOSTTOPN532;
	
	u.sendBytes(header, hlen);
	
	for (uint8_t i = 0; i < hlen; i++) {
		sum += header[i];
	}
	
	u.sendBytes(body, blen);
	
	for (uint8_t i = 0; i < blen; i++) {
		sum += body[i];
	}
	
	uint8_t checksum = ~sum + 1;
	u.sendChar(checksum);
	u.sendChar(PN532_POSTAMBLE);
	return readAckFrame();
}

uint16_t PN532::readResponse(uint8_t buf[], uint8_t len, uint16_t timeout)
{
	uint8_t tmp[3];
	if(receive(tmp, 3, timeout)<=0){
		return PN532_TIMEOUT;
	}
	
	if(0 != tmp[0] || 0!= tmp[1] || 0xFF != tmp[2]){
		return PN532_INVALID_FRAME;
	}
	
	uint8_t length[2];
	if(receive(length, 2, timeout) <= 0){
		return PN532_TIMEOUT;
	}
	if( 0 != (uint8_t)(length[0] + length[1]) ){
		return PN532_INVALID_FRAME;
	}
	
	length[0] -= 2;
	if( length[0] > len){
		return PN532_NO_SPACE;
	}
	
	uint8_t cmd = command + 1;               // response command
	if(receive(tmp, 2, timeout) <= 0){
		return PN532_TIMEOUT;
	}
	if( PN532_PN532TOHOST != tmp[0] || cmd != tmp[1]){
		return PN532_INVALID_FRAME;
	}
	
	if(receive(buf, length[0], timeout) != length[0]){
		return PN532_TIMEOUT;
	}
	
	uint8_t sum = PN532_PN532TOHOST + cmd;
	for(uint8_t i=0; i<length[0]; i++){
		sum += buf[i];
	}
	
	/** checksum and postamble */
	if(receive(tmp, 2, timeout) <= 0){
		return PN532_TIMEOUT;
	}
	if( 0 != (uint8_t)(sum + tmp[0]) || 0 != tmp[1] ){
		return PN532_INVALID_FRAME;
	}
	
	return length[0];
}

int8_t PN532::receive(uint8_t *buf, int len, uint16_t timeout/*=1000*/)
{
	int read_bytes = 0;
	int ret;
	unsigned long start_millis;
	
	while (read_bytes < len) {
		ret = u.recieveChar(timeout);
		
		if (ret < 0) {
			if(read_bytes){
				return read_bytes;
				}else{
				return PN532_TIMEOUT;
			}
		}
		buf[read_bytes] = (uint8_t)ret;
		read_bytes++;
	}
	return read_bytes;
}

int8_t PN532::readAckFrame()
{
	const uint8_t PN532_ACK[] = {0, 0, 0xFF, 0, 0xFF, 0};
	uint8_t ackBuf[sizeof(PN532_ACK)];
	
	if( receive(ackBuf, sizeof(PN532_ACK), PN532_ACK_WAIT_TIME) <= 0 ){
		return PN532_TIMEOUT;
	}
	
	if( memcmp(ackBuf, PN532_ACK, sizeof(PN532_ACK)) ){
		return PN532_INVALID_ACK;
	}
	return 0;
}




