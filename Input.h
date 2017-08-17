/* 
* Input.h
*
* Created: 17.08.2017
* Author: kevin
*/


#ifndef __INPUT_H__
#define __INPUT_H__

#include <avr/io.h>
#include <stdio.h>

class Input
{
//variables
public:
protected:
private:
	uint8_t Port;
	uint8_t Pin;

//functions
public:
	Input(uint8_t Portadresse, uint8_t Pinnumber, uint8_t pullup);
	~Input();
	uint8_t ison();
protected:
private:
	Input( const Input &c );
	Input& operator=( const Input &c );

}; //Input

#endif //__INPUT_H
