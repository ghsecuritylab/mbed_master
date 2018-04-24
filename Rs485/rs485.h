/*
 * rs485.h
 *
 *  Created on: 18 Mar 2018
 *      Author: christo
 */

#ifndef RS485_RS485_H_
#define RS485_RS485_H_

#include <stdint.h>

#include "mbed.h"
#include "Console.h"
#include "hdlc_framer.h"
#include "c_msg.h"

class RS485 {
	static RS485 *__instance;
	Serial *mSerial;
	DigitalOut *mWriteEnable;
	cHDLCframer *framer;

	void writeEnable(bool enable);
public:
	RS485(Serial *serial, DigitalOut *writeEnable);
	virtual ~RS485();

	static void init(Serial *serial, DigitalOut *writeEnable);
	static void sendbytes(uint8_t *data, uint32_t len);
};

extern const Console::cmd_list_t rs485Commands[];

#endif /* RS485_RS485_H_ */
