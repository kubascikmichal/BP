/* 
* SoftUART.cpp
*
* Created: 6.11.2020 18:36:50
* Author: Dominik
*/


#include "../Headers/SoftUART.h"


// default constructor
SoftUART::SoftUART() {
	
	//set S_TX - OUTPUT; S_RX - INPUT
	sbi(DDRC, S_TX);
	cbi(DDRC, S_RX);
	
	sbi(PORTC, S_TX);
	sbi(PORTC, S_RX);
	
	uart_ptr = fdevopen(SoftUART::sendByte, SoftUART::receiveByte);
	stdout = stdin = uart_ptr;
	
} //SoftUART

// default destructor
SoftUART::~SoftUART() {
	
} //~SoftUART

int SoftUART::sendByte(char data, FILE *stream) {
	if (data == '\n') {
		sendByte('\r', 0);
	}
	sendByteS(data);
	return 0;
}

int SoftUART::receiveByte(FILE *stream) {
	char data;
	data = receiveByteS();
	return data;
}

void SoftUART::send(const char* word) {
	for (uint8_t i = 0; i < strlen(word); i++) {
		sendByte(word[i], 0);
	}	
}

char* SoftUART::receive(char* buffer) {
	char data;
	int index = 0;
	
	while (index != BUFFER_SIZE) {
		data = receiveByte(0);
		
		//ASCII 13 'ENTER'
		if (data == 13) {
			buffer[index] = '\0';
			this->send("\n\r");
			return buffer;
		}
		buffer[index] = data;
		this->sendByte(buffer[index++], 0);
		
	}
	this->send("\nbuffer overflow!!!\n");
	return 0;
}

void SoftUART::sendByteS(uint8_t data) {	
	
	//start bit
	cbi(PORTC, S_TX);
	_delay_us(104);
	
	//send data 8bit
	for (int i = 0; i < 8; i++) {
		if (data & 1) {
			sbi(PORTC, S_TX);
		} else {
			cbi(PORTC, S_TX);
		}
		data = data >> 1;
		_delay_us(104);
	}
	//stop bit
	sbi(PORTC, S_TX);
	_delay_us(104);
		
}

uint8_t SoftUART::receiveByteS(void) {
	
	uint8_t data = 0;
	
	//wait for start bit
	while ((PINC & (1<<S_RX)) != 0) {}
	_delay_us(52);
	
	//read data 8bit
	for (int i = 0; i < 8; i++) {
		data = data >> 1;	
		_delay_us(104);
		
		if ((PINC & (1<<S_RX)) != 0) {
			data = data | 0b10000000;
		}
	}
	return data;
}

 