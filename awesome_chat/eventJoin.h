#include "event.h"
#include <iostream>


MK_EVENT(EventJoin)
{
public:
    EventJoin(std::string user, std::string room);
    ~EventJoin();
    
	static std::shared_ptr<RawPacket> ToByte()
	{
		for(int i = 0; i<size; i++)
			std::cout<<packet[i];
		std::cout<<std::endl;
	}

	static std::shared_ptr<RawPacket> ToByte(Join& data)
	{
		std::cout<<"Enter"<<std::endl;
		std::shared_ptr<RawPacket> temp = std::shared_ptr<RawPacket>(new RawPacket(3));

		temp->Packet()[0] = 1;
		temp->Packet()[1] = 2;
		temp->Packet()[2] = 3;

		return temp;
	}

	static Join FromByte(uint8_t* packet, std::size_t size)
	{
		std::cout<<"Exit"<<std::endl;
		return Join(packet, size);
	}
};



