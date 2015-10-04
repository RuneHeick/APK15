//
//  clientInfo.h
//  ac
//
//  Created by Michael Rahlff on 03/10/15.
//  Copyright (c) 2015 Michael Rahlff. All rights reserved.
//

#ifndef __ac__clientInfo__
#define __ac__clientInfo__

#include <stdio.h>
#include <string>
#include <boost/signals2.hpp>
#include <boost/variant.hpp>
#include "NetSocket.h"
#include "event.h"
#include <mutex>
#include <thread>

template<typename TVariant>
class ClientInfo {
public:

	typedef TVariant VariantType;
	typedef void (*HandlerType)(ClientInfo<TVariant>, TVariant);

	ClientInfo(Client clientsocket):client(clientsocket)
	{

	}

	void Send(Interface& type)
	{
		std::unique_lock<std::mutex> lock(writeMutex, std::try_to_lock);
		//client.write(type.ToByte());
	}

	void AddRecivedHandler(HandlerType handler)
	{
		recivedPacket.connect(handler);
	}

	void RemoveRecivedHandler(HandlerType handler)
	{
		recivedPacket.disconnect(handler);
	}

	std::string Name;
private:
	std::mutex writeMutex;
	Client client;
	boost::signals2::signal<void (ClientInfo<TVariant>, VariantType)> recivedPacket;
	/*
	void threadRun()
	{
		while(client.IsOpen())
		{
			auto packet = client.read();
			if(packet->Size()>0)
			{


			}
		}
	}
	*/

};

#endif /* defined(__ac__clientInfo__) */
