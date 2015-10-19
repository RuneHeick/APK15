#ifndef EVENTWHO_H_
#define EVENTWHO_H_

#include "event.h"
#include <string>
#include <iostream>
#include "../RawPacket.h"

MK_EVENT(EventWho)
{
public:

	EventWho() = default;

    ~EventWho()
    {}
    
	static std::shared_ptr<RawPacket> ToByte(EventWho& data)
	{
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(0));
		return temp;
	}

	static EventWho FromByte(uint8_t* packet, std::size_t size)
	{
		return EventWho();
	}

    
};
#endif
