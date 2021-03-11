/* 
* PN532.cpp
*
* Created: 21. 2. 2021 14:07:06
* Author: Michal Kubascik
*/


#include "../Headers/PN532.h"

// default constructor
PN532::PN532(){
	
} //PN532

 
PN532::~PN532(){
	
} //~PN532

bool PN532::readPassiveTargetID(uint8_t cardbaudrate, uint8_t *uid, uint8_t *uidLength, uint16_t timeout){
  pn532_packetbuffer[0] = PN532_COMMAND_INLISTPASSIVETARGET;
  pn532_packetbuffer[1] = 1; // max 1 cards at once (we can set this to 2 later)
  pn532_packetbuffer[2] = cardbaudrate;
  
	if(!i2c.master_transmit(PN532_ADDRESS, pn532_packetbuffer, 3, false)){
	return 0x00;  
	}
	
	i2c.master_receive(PN532_ADDRESS, pn532_packetbuffer, 20);
	if(pn532_packetbuffer[7] !=1) {
		return 0;
	} else {
		return 1;
	}
}

uint8_t PN532::setSAMConfig()
{
	  pn532_packetbuffer[0] = PN532_COMMAND_SAMCONFIGURATION;
	  pn532_packetbuffer[1] = 0x01; // normal mode;
	  pn532_packetbuffer[2] = 0x14; // timeout 50ms * 20 = 1 second
	  pn532_packetbuffer[3] = 0x01; // use IRQ pin!

	  writeData(pn532_packetbuffer, 4);
	  // read data packet
	  //i2c.master_receive(PN532_ADDRESS, pn532_packetbuffer, 8);
	  int offset = 6;
	  return (pn532_packetbuffer[offset] == 0x15);

}

uint32_t PN532::getFirmwareVersion(){
uint32_t response = 0;

pn532_packetbuffer[0] = PN532_COMMAND_GETFIRMWAREVERSION;

	i2c.start();
	i2c.write_sla(SLA_W_ADD(PN532_ADDRESS));
	i2c.write(PN532_PREAMBLE);
	i2c.write(PN532_PREAMBLE);
	i2c.write(PN532_STARTCODE2);
	i2c.write(2);
	i2c.write(~1 + 1);
	i2c.write(PN532_HOSTTOPN532);
	uint8_t checksum;
	i2c.write(PN532_COMMAND_GETFIRMWAREVERSION);
	checksum = PN532_PREAMBLE+PN532_PREAMBLE+PN532_STARTCODE2+PN532_HOSTTOPN532;
	checksum+=PN532_COMMAND_GETFIRMWAREVERSION;
	i2c.write(~checksum);
	i2c.write(PN532_POSTAMBLE);
	i2c.stop();
	i2c.master_receive(PN532_ADDRESS, pn532_packetbuffer, 12);
	
	int offset = 7;
	response = pn532_packetbuffer[offset++];
	response <<= 8;
	response |= pn532_packetbuffer[offset++];
	response <<= 8;
	response |= pn532_packetbuffer[offset++];
	response <<= 8;
	response |= pn532_packetbuffer[offset++];
	return response;
}


uint8_t PN532::writeData(uint8_t* data, uint8_t dataLength) {
	dataLength++;
	uint8_t checksum;
	i2c.start();
	i2c.write_sla(SLA_W_ADD(PN532_ADDRESS));
	i2c.write(PN532_PREAMBLE);
	i2c.write(PN532_PREAMBLE);
	checksum=2*PN532_PREAMBLE;
	i2c.write(PN532_STARTCODE2);
	checksum+=PN532_STARTCODE2;
	i2c.write(dataLength);
	i2c.write(~dataLength + 1);
	i2c.write(PN532_HOSTTOPN532);
	checksum+=PN532_HOSTTOPN532;
	for(int i = 0; i < dataLength; i++) {
		i2c.write(data[i]);
		checksum+=data[i];
}
	i2c.write(~checksum);
	i2c.write(PN532_POSTAMBLE);
	i2c.stop();
}

