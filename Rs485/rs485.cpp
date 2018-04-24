/*
 * rs485.cpp
 *
 *  Created on: 18 Mar 2018
 *      Author: christo
 */

#include "rs485.h"


//#include <stdio.h>

#include <string.h>



RS485::RS485(Serial *serial, DigitalOut *writeEnable) : mSerial(serial), mWriteEnable(writeEnable)
{
	framer = new cHDLCframer(64, 1);
//	USART1->CR1 |= USART_CR1_TXEIE;
	USART1->CR1 |= USART_CR1_RXNEIE;
	HAL_NVIC_SetPriority(USART1_IRQn, 0x1, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

}

RS485::~RS485()
{
	delete(framer);
	delete(__instance);
	__instance = 0;
}

RS485 *RS485  ::__instance = 0;

void RS485::init(Serial *serial, DigitalOut *writeEnable)
{
	if(!__instance)
		__instance = new RS485(serial, writeEnable);
}

void RS485::writeEnable(bool enable)
{
	if(enable)
		__instance->mWriteEnable->write(SET);
	else
		__instance->mWriteEnable->write(RESET);
}

void RS485::sendbytes(uint8_t *data, uint32_t len)
{
	uint8_t framedData[64];
	uint32_t framedLen = 0;
	__instance->framer->frame(data, len, framedData, &framedLen);

	__instance->writeEnable(true);

	for(uint32_t i=0; i<framedLen; i++)
	{
//		__instance->mSerial->putc(framedData[i]);
		USART1->DR = framedData[i];
		while (!(USART1->SR & USART_SR_TC));
	}
//
//	int i = 0;
//	while (!(USART1->SR & USART_SR_TC))
//		{
//		if(i++ > 25000)
//			break;
//		}
//
//	printf("i: %d\n", (int)i);
//	wait(0.001);
	__instance->writeEnable(false);
//	printf("485 out: ");
//	for(uint32_t i=0; i<framedLen; i++)
//		printf(" %02X", framedData[i]);
//	printf("\r\n");
}

extern "C"
{
void USART1_IRQHandler(void)
{
	uint8_t data = USART1->DR;
	printf("%02X", data);
}
}
