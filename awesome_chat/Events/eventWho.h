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

    EventWho(std::string usr){
        user = usr;
    }

    ~EventWho()
    {}
    
	static std::shared_ptr<RawPacket> ToByte(EventWho& data)
	{
		std::cout<<"Enter"<<std::endl;
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(3));

		temp->Packet()[0] = 1;
		temp->Packet()[1] = 2;
		temp->Packet()[2] = 3;

		return temp;
	}

	static EventWho FromByte(uint8_t* packet, std::size_t size)
	{
		std::cout<<"Exit"<<std::endl;
		return EventWho("moo");
	}

private:
    std::string user;
    
};
#endif
