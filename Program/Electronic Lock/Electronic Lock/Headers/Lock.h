/* 
* Lock.h
*
* Created: 21. 2. 2021 14:07:25
* Author: Michal Kubascik
*/


#ifndef __LOCK_H__
#define __LOCK_H__

#include "Board.h"

class Lock
{
//variables
public:
protected:
private:

//functions
public:
	Lock();
	~Lock();
	
	void lock();
	void unlock();
	bool getState(); //?
	
protected:
private:

}; //Lock

#endif //__LOCK_H__
