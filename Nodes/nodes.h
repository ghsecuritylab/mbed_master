/*
 * nodes.h
 *
 *  Created on: 24 Mar 2018
 *      Author: christo
 */

#ifndef NODES_NODES_H_
#define NODES_NODES_H_

#include "Console.h"
#include "rs485.h"

class cNodes {
	static cNodes *__instance;

	static void pollDevice(uint8_t address);
public:
	cNodes();
	virtual ~cNodes();

	static void init();
	static void poll(int argc,char *argv[]);
};

extern const Console::cmd_list_t nodeCommands[];

#endif /* NODES_NODES_H_ */
