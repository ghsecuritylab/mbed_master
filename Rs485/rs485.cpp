/*
 * rs485.cpp
 *
 *  Created on: 18 Mar 2018
 *      Author: christo
 */

#include "rs485.h"



RS485::RS485(Serial *serial) : mSerial(serial)
{
	// TODO Auto-generated constructor stub

}

RS485::~RS485()
{
	// TODO Auto-generated destructor stub
}

RS485 *RS485  ::__instance = 0;

void RS485::init(Serial *serial)
{
	if(!__instance)
		__instance = new RS485(serial);
}

void RS485::sendString(int argc,char *argv[])
{
	if(argc == 2)
	{
		const char *str = argv[1];
		printf("send %s\r\n", str);
		__instance->mSerial->printf("%s", str);
	}
}

const Console::cmd_list_t rs485Commands[] =
{
      {"RS 485"    ,0,0,0},
      {"ss",       "", "send a string to serial port", RS485::sendString},
      {0,0,0}
};
