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
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(3));

		temp->Packet()[0] = 1;
		temp->Packet()[1] = 2;
		temp->Packet()[2] = 3;

		return temp;
	}


	static EventMsg FromByte(uint8_t* packet, std::size_t size)
	{
		std::cout<<"Exit"<<std::endl;
		return EventMsg("Rune", "hej");
	}
private:
    std::string sender_;
    std::string msg_;
    
};

#endif
