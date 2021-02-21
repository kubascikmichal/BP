/* 
* Lock.cpp
*
* Created: 21. 2. 2021 14:07:25
* Author: Michal Kubascik
*/


#include "../Headers/Lock.h"

// default constructor
Lock::Lock(){
	sbi(DDRD, LOCK_PIN);
} //Lock

// default destructor
Lock::~Lock()
{
} //~Lock

void Lock::lock(){
	cbi(PORTD, LOCK_PIN);
}

void Lock::unlock(){
	sbi(PORTD, LOCK_PIN);
}

bool Lock::getState(){
	return (PORTD&(1<<LOCK_PIN));
}
