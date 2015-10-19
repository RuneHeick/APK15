#ifndef EVENTMSG_H_
#define EVENTMSG_H_

#include "event.h"
#include <string>
#include <iostream>
#include "../RawPacket.h"


MK_EVENT(EventMsg)
{
public:
	EventMsg() = default;

    EventMsg(std::string sender, std::string msg){
        sender_ = sender;
        msg_ = msg;
    }

    ~EventMsg()
    {

    }

	static std::shared_ptr<RawPacket> ToByte(EventMsg& data)
	{
		std::cout<<"Enter"<<std::endl;
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(1+data.sender_.length()+1+data.msg_.length())); // name + \0 + msg+ \0
		std::memcpy(&(*temp)[0], data.sender_.c_str(), data.sender_.length()+1);
		std::memcpy(&(*temp)[1+data.sender_.length()], data.msg_.c_str(), data.msg_.length()+1);

		return temp;
	}


	static EventMsg FromByte(uint8_t* packet, std::size_t size)
	{
		std::string tempname(reinterpret_cast <char*>(packet));
		std::string tempmsg(reinterpret_cast <char*>(&packet[tempname.length()+1]));

		return EventMsg(tempname,tempmsg);
	}
    
    std::string getSender()
    {
        return sender_;
    }
    
    std::string getMessage()
    {
        return msg_;
    }
private:
    std::string sender_;
    std::string msg_;
    
};

#endif
