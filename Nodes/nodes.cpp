/*
 * nodes.cpp
 *
 *  Created on: 24 Mar 2018
 *      Author: christo
 */

#include <nodes.h>
#include "c_msg.h"
cNodes::cNodes() {
	// TODO Auto-generated constructor stub

}

cNodes::~cNodes() {
	// TODO Auto-generated destructor stub
}

void cNodes::init()
{
	if(__instance == 0)
		__instance = new cNodes;
}

void cNodes::pollDevice(uint8_t address)
{
	cmsg_t msg;
	memset(&msg, 0x00, sizeof(cmsg_t));
	msg.address = address;
	msg.type = CMSG_TYPE_GET;
	msg.tag = CMSG_TAG_PING;

	uint8_t bytes[sizeof(cmsg_t)];
	memcpy(&bytes, &msg, sizeof(cmsg_t));
	RS485::sendbytes(bytes, sizeof(cmsg_t));
}

void cNodes::poll(int argc,char *argv[])
{
	pollDevice(0);
}

const Console::cmd_list_t nodeCommands[] =
{
      {"NODES"    ,0,0,0},
      {"np",      "",                   "Poll the nodes", cNodes::poll},
      {0,0,0}
};
