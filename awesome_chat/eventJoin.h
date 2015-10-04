#include "event.h"


MK_EVENT(Join)
{
	static std::shared_ptr<RawPacket> ToByte()
	{
		return std::shared_ptr<RawPacket>();
	}

	static void FromByte(std::shared_ptr<RawPacket> p)
	{

	}
};



