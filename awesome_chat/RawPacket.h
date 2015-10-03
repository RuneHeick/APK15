/*
 * RawPacket.h
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#ifndef RAWPACKET_H_
#define RAWPACKET_H_

#include <stdint.h>
#include <stddef.h>

class RawPacket {
public:
	RawPacket(size_t len);
	virtual ~RawPacket();

	uint8_t* Packet();
	size_t Size();

private:
	uint8_t * packet;
	size_t size;
};

#endif /* RAWPACKET_H_ */
