/*
 * c_msg.h
 *
 *  Created on: 21 Mar 2018
 *      Author: christo
 */

#ifndef UTILS_C_MSG_H_
#define UTILS_C_MSG_H_

typedef enum{
	CMSG_TYPE_SET,
	CMSG_TYPE_GET
}cmsg_types_t;

typedef enum{
	CMSG_TAG_PING,
	CMSG_TAG_PWM,
	CMSG_TAG_INPUT,
}cmsg_tags_t;

typedef struct{
	uint8_t address;
	cmsg_types_t type;
	cmsg_tags_t tag;
	uint8_t data0;
	uint8_t data1;
}cmsg_t;



#endif /* UTILS_C_MSG_H_ */

