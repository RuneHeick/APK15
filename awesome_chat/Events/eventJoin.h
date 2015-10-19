
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
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(1+data.userName_.length()+1+data.targetRoom_.length())); // name + \0 + msg+ \0
		std::memcpy(temp->Packet(), data.userName_.c_str(), data.userName_.length()+1);
		std::memcpy(&temp->Packet()[1+data.userName_.length()], data.targetRoom_.c_str(), data.targetRoom_.length()+1);

		return temp;
	}

	static EventJoin FromByte(uint8_t* packet, std::size_t size)
	{
		std::string tempname(reinterpret_cast <char*>(packet));
		std::string temproom(reinterpret_cast <char*>(&packet[tempname.length()+1]));

		return EventJoin(tempname,temproom);
	}
    
    std::string getUser()
    {
        return userName_;
    }
    
    std::string getTargetRoom()
    {
        return targetRoom_;
    }
private:
    std::string userName_;
    std::string targetRoom_;
};

#endif
