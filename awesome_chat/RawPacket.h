/*
 * RawPacket.h
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#ifndef RAWPACKET_H_
#define RAWPACKET_H_
#include <cstdlib>
#include <stdint.h>

class RawPacket {
public:
	RawPacket(std::size_t len);
	virtual ~RawPacket();

	uint8_t* Packet();
	std::size_t Size();

private:
	uint8_t * packet;
	std::size_t size;
};

#endif /* RAWPACKET_H_ */
