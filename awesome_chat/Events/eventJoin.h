
#ifndef EVENTJOIN_H_
#define EVENTJOIN_H_

#include "event.h"
#include <iostream>
#include "../RawPacket.h"


MK_EVENT(EventJoin)
{
public:
    EventJoin() = default;
    EventJoin(std::string user, std::string room)
    {
        userName_ = user;
        targetRoom_ = room;
    }

    ~EventJoin()
    {

    }
    
	static std::shared_ptr<RawPacket> ToByte(EventJoin& data)
	{
		std::cout<<"Enter"<<std::endl;
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(3));

		temp->Packet()[0] = 1;
		temp->Packet()[1] = 2;
		temp->Packet()[2] = 3;

		return temp;
	}

	static EventJoin FromByte(uint8_t* packet, std::size_t size)
	{
		std::cout<<"Exit"<<std::endl;
		return EventJoin();
	}
private:
    std::string userName_;
    std::string targetRoom_;
};

#endif
