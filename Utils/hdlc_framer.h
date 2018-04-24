/*
 * hdlc_framer.h
 *
 *  Created on: 21 Mar 2018
 *      Author: christo
 */

#ifndef UTILS_HDLC_FRAMER_H_
#define UTILS_HDLC_FRAMER_H_

#include <stdint.h>

#include "mbed.h"

class cHDLCframer
{
    uint8_t mCrcBytes;
	uint8_t *mBuffer;
	uint32_t mLength;
	uint32_t mFrameIdx;
	bool mValidFrame;
	bool mEscapeChar;

	// --------------------------------------------------
    // Add a byte to a HDLC frame,
    // --------------------------------------------------
    static void add_byte(uint8_t byte, uint8_t  * frame_ptr, uint32_t * frame_length);

public:
	// ----------------- cHDLCframer ---------------------------
	// Use pack() to start packing bytes of an HDLC frame into buff_ptr
	//
	// When pack returns a value, a valid frame has been received
	cHDLCframer(uint32_t buff_len, uint8_t crc_bytes);
	virtual ~cHDLCframer();

	// --------------------------------------------------
	// Create an HDLC frame from input pay load
	// --------------------------------------------------
	// payload_ptr points to a buffer which should contain
	// at least two command bytes. Up to 64 additional
	// data bytes may also be contained within the buffer,
	// but they are optional.
	// --------------------------------------------------
	// payload_length specifies how many bytes are in the
	// pay load buffer
	// --------------------------------------------------
	// frame_ptr points to a buffer which should be 138 bytes.
	// The pay load will be encapsulated within this frame,
	// along with two flag bytes and two FCS bytes.
	// --------------------------------------------------
	// frame_length returns the number of bytes within the frame
	// --------------------------------------------------
    void frame(uint8_t * payload_ptr,
    						uint32_t payload_length,
							uint8_t * frame_ptr,
							uint32_t * frame_length);

    // --------------------------------------------------
	// Get the data in an HDLC frame buff with len length
	// --------------------------------------------------
   /* static uint32_t unFrame(uint8_t* buff,
    							uint32_t len,
								uint8_t* returnBuff);*/

    // --------------------------------------------------
	// Pack bytes from a input device into a HDLC frame
	// --------------------------------------------------
    // - Frames are packed in mBuffer, starting with a 0x7E and ended with a 0x7E,
	// - The last two bytes of the frame are the crc16 bytes
	// - Once a complete valid frame is packed, it returns the frame length
	//   and it is available where mBuffer pointed to
	// - If the frame had errors it returns -1
    int pack(uint8_t byte);

    uint8_t* buffer(){ return mBuffer; };


};


#endif /* UTILS_HDLC_FRAMER_H_ */
