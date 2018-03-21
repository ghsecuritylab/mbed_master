/*
 * rs485.h
 *
 *  Created on: 18 Mar 2018
 *      Author: christo
 */

#ifndef RS485_RS485_H_
#define RS485_RS485_H_

#include "mbed.h"
#include "Console.h"

class RS485 {
	static RS485 *__instance;
	Serial *mSerial;
public:
	RS485(Serial *serial);
	virtual ~RS485();

	static void init(Serial *serial);
	static void sendString(int argc,char *argv[]);
};

extern const Console::cmd_list_t rs485Commands[];

#endif /* RS485_RS485_H_ */
