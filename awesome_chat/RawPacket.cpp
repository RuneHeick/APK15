/*
 * RawPacket.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#include "RawPacket.h"

RawPacket::RawPacket(std::size_t buffersize) {
	size = buffersize;
	packet = new uint8_t[size];
}

RawPacket::~RawPacket() {
	delete[] packet;
}

uint8_t* RawPacket::Packet()
{
	return packet;
}

std::size_t RawPacket::Size()
{
	return size;
}
