/*
 * crc.h
 *
 *  Created on: 21 Mar 2018
 *      Author: christo
 */

#ifndef UTILS_CRC_H_
#define UTILS_CRC_H_

#include "mbed.h"

class cCrc
{
    static const uint16_t cCrcTable[256];

    static void add_byte(uint8_t byte, uint8_t  * frame_ptr, uint32_t * frame_length);

public:
    static uint8_t crc8(uint8_t * data,uint32_t len);
    static uint8_t crc8_update(uint8_t data,uint8_t crc);
    static uint16_t ccitt_crc16(uint8_t data,uint16_t crc_acc);
    static uint16_t ccitt_crc16(uint8_t * data_ptr,uint32_t len);

    static const uint16_t INIT_CRC;
    static const uint16_t GOOD_CRC;
};
#endif /* UTILS_CRC_H_ */
