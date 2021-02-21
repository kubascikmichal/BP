/*
 * Commands.h
 *
 * Created: 21. 2. 2021 16:22:15
 *  Author: Michal Kubascik
 */ 


#ifndef COMMANDS_H_
#define COMMANDS_H_

//TODO: PN532 command messages
//https://www.nxp.com/docs/en/user-guide/141520.pdf

//Miscellaneous
#define PN532_DIAGNOSE					0x00
#define PN532_GET_FIRMWARE_VERSION		0x02
#define PN532_GET_GENERAL_STATUS		0x04
#define PN532_READ_REGISTER				0x06
#define PN532_WRITE_REGISTER			0x08
#define PN532_READ_GPIO					0x0C
#define PN532_WRITE_GPIO				0x0E
#define PN532_SET_SERIAL_BAUDRATE		0x10
#define PN532_SET_PARAMETERS			0x12
#define PN532_SAM_CONFIGURATION			0x14
#define PN532_POWER_DOWN				0x16

//RF communication
#define PN532_RF_CONFIGURATION			0x32
#define PN532_RF_REGULATION_TEST		0x58

//Initiator
#define PN532_IN_JUMP_FOR_DEP			0x56
#define PN532_IN_JUMP_FOR_PSL			0x46
#define PN532_IN_LIST_PASSIVE_TARGET	0x4A
#define PN532_IN_ATR					0x50
#define PN532_IN_PSL					0x4E
#define PN532_IN_DATA_EXCHANGE			0x40
#define PN532_IN_COMMUNICATION_THRU		0x42
#define PN532_IN_DESELECT				0x44
#define PN532_IN_RELEASE				0x52
#define PN532_IN_SELECT					0x54
#define PN532_IN_AUTO_POLL				0x60

//Target
#define PN532_TG_INIT_AS_TARGET			0x8C
#define PN532_TG_SET_GENERAL_BYTES		0x92
#define PN532_TG_GET_DATA				0x86
#define PN532_TG_SET_DATA				0x8E
#define PN532_TG_SET_META_DATA			0x94
#define PN532_TG_GET_INITIATOR_COMMAND	0x88
#define PN532_TG_RESPONSE_TO_INITIATOR	0x90
#define PN532_TG_GET_TARGET_STATUS		0x8A

//Error codes
//TODO: ATWIN command messages



#endif /* COMMANDS_H_ */