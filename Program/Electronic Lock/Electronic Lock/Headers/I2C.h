/* 
* I2C.h
*
* Created: 21. 2. 2021 14:44:38
* Author: Michal Kubascik
*/


#ifndef __I2C_H__
#define __I2C_H__


class I2C
{
//variables
public:
protected:
private:

//functions
public:
	I2C();
	~I2C();
	
	I2C(int sda, int scl);
protected:
private:
	int sda;
	int scl;

}; //I2C

#endif //__I2C_H__
