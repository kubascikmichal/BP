/*
* MANAGEMENT.h
*
* Created: 21. 2. 2021 15:55:37
* Author: Michal Kubascik
*/

#include "Board.h"
#include <avr/eeprom.h>
#include <stdlib.h>
#include <string.h>

#define UID_LEN 8
#define COUNT_ADD 0
#define ADMIN_ADD 1
#define APPROVED_START_ADD (ADMIN_ADD + UID_LEN)
#define APPROVED_ADD(x) (APPROVED_START_ADD + (x*UID_LEN))
#define EEPROM_WAIT while(!eeprom_is_ready());

#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__


class MANAGEMENT
{
	//variables
	public:
	typedef uint8_t cUID[UID_LEN];
	protected:
	private:
	uint8_t countOfCards;
	cUID* cards;
	uint8_t size;
	cUID admin;
	

	//functions
	public:
	MANAGEMENT();
	~MANAGEMENT();
	bool addCard(cUID* uid);
	bool removeCard(cUID* uid);
	uint8_t matchCards(cUID* uid, uint8_t* index = 0);
	void factoryReset();
	void refresh();
	cUID* getCUID(uint8_t index);
	uint8_t getCountOfCards();
	cUID* getAdmin();
	protected:
	private:
	void reset();
	void init();
	bool compare(cUID* cuid1, cUID* cuid2);

}; //MANAGEMENT

#endif //__MANAGEMENT_H__
