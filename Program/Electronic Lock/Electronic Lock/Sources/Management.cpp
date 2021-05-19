/*
* EEPROM.cpp
*
* Created: 21. 2. 2021 15:55:37
* Author: Michal Kubascik
*/


#include "../Headers/Management.h"

//UART u;
// default constructor
MANAGEMENT::MANAGEMENT(){
	countOfCards = 0;
	size = 2;
	cards = (cUID*) malloc(size*sizeof(cUID));
	EEPROM_WAIT
	int tmp = eeprom_read_byte(COUNT_ADD);
	if(tmp == 255) {
		tmp = 0;
		EEPROM_WAIT
		eeprom_write_byte(COUNT_ADD, 0);
	}
	printf("%d", tmp);
	EEPROM_WAIT
	eeprom_read_block(&admin, (void*)ADMIN_ADD, UID_LEN);
	for (int i = 0; i < tmp; i++){
		cUID c;
		EEPROM_WAIT
		eeprom_read_block(&c, (void *) APPROVED_ADD(i), UID_LEN);
		addCard(&c, false);
	}
	
} //MANAGEMENT

// default destructor
MANAGEMENT::~MANAGEMENT()
{
} //~MANAGEMENT

bool MANAGEMENT::addCard(cUID* uid, bool eepromAlowed){
	if(this->admin[0] == 255) {
		memcpy(&admin, *uid, UID_LEN);
		if(eepromAlowed){
			EEPROM_WAIT
			eeprom_write_block(uid, (void*)ADMIN_ADD, UID_LEN);
		}
		return true;
	}
	uint8_t t = matchCards(uid);
	if(t != 0) {
		return false;
	}
	if(countOfCards == size) {
		cards = (cUID*) realloc(cards, size*2*sizeof(cUID));
		size = size*2;
	}
	memcpy(cards[countOfCards], *uid, UID_LEN);
	
	if(eepromAlowed) {
		printf("adding to eeprom");
		EEPROM_WAIT
		eeprom_write_block(uid, (void*)APPROVED_ADD(countOfCards++), UID_LEN);
		EEPROM_WAIT
		eeprom_write_byte(COUNT_ADD, countOfCards);
	} else {
		countOfCards++;
	}
	
	return true;
}

bool MANAGEMENT::removeCard(cUID* uid){
	uint8_t index;
	uint8_t founded = matchCards(uid, &index);
	if(founded == 0) {
		return false;
		} else if (founded == 1){
		return false;
	}
	memcpy(&(this->cards[index]), &(this->cards[--countOfCards]), UID_LEN);
	EEPROM_WAIT
	eeprom_write_byte(COUNT_ADD, countOfCards);
	cUID tmp;
	EEPROM_WAIT
	eeprom_read_block(&tmp, (void*) APPROVED_ADD((countOfCards)), UID_LEN);
	EEPROM_WAIT
	eeprom_write_block(&tmp, (void*) APPROVED_ADD(index), UID_LEN);
	EEPROM_WAIT
	eeprom_read_block(&tmp, (void*) APPROVED_ADD((countOfCards+1)), UID_LEN);
	EEPROM_WAIT
	eeprom_write_block(&tmp, (void*) APPROVED_ADD(countOfCards), UID_LEN);
	return true;
}

/*
uid - pointer to uID for check
return value:
0 for no match
1 for match with admin
2 for match for one of approved cards
index will be filled only if return value is more than 0
*/
uint8_t MANAGEMENT::matchCards(cUID* uid, uint8_t* index){
	if(compare(&admin, uid)) {
		return 1;
	}
	
	for(uint8_t i = 0; i < countOfCards; i++) {
		if(compare(&(this->cards[i]), uid)) {
			*index = i;
			return 2;
		}
	}
	*index = 0;
	return 0;
}

void MANAGEMENT::factoryReset()
{
	for (int i = 0; i < 1024; i++){
		EEPROM_WAIT
		eeprom_write_byte((uint8_t*)i,0);
	}
}

void MANAGEMENT::reset()
{
	for (int i = 7; i < 1024; i++){
		EEPROM_WAIT
		eeprom_write_byte((uint8_t*)i,0);
	}
}

void MANAGEMENT::init(){
	for (int i = APPROVED_START_ADD; i < countOfCards*UID_LEN; i++){
		//eeprom_read_byte((uint8_t*)i,0);
	}
}

bool MANAGEMENT::compare(cUID* cuid1, cUID* cuid2){
	for(uint8_t index = 0; index < UID_LEN; index++) {
		if((*cuid1)[index] != (*cuid2)[index]) {
			return false;
		}
	}
	return true;
}

void MANAGEMENT::refresh()
{
	//delete and read aproved cards again
	//is it important?
	
}

MANAGEMENT::cUID* MANAGEMENT::getCUID(uint8_t index)
{
	if(index < countOfCards) {
		return &(this->cards[index]);
		} else {
		return 0;
	}
}

uint8_t MANAGEMENT::getCountOfCards()
{
	return this->countOfCards;
}

MANAGEMENT::cUID* MANAGEMENT::getAdmin(){
	return &this->admin;
}

