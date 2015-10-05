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
#include "EventSerilizer.h"
#include <boost/system/system_error.hpp>

template<typename TList>
class ClientInfo {
public:

	typedef typename boost::make_variant_over<TList>::type TVariant;

	typedef void (*HandlerType)(ClientInfo<TVariant>*, TVariant);
	typedef void (*DisconnectedHandlerType)(ClientInfo<TVariant>*);


	ClientInfo(Simple_Socket clientsocket): client(clientsocket)
	{
		if(clientsocket.IsOpen())
		{
			isOpen = true;
			m_thread = std::thread(&ClientInfo::threadRun, this);
		}
		else
		{
			throw boost::system::system_error(boost::asio::error::not_connected );
		}
	}

	void Send(TVariant& type)
	{
		std::unique_lock<std::mutex> lock(socketMutex, std::try_to_lock);
		if(isOpen)
		{
			try
			{
			client.write(serilizer.serilize(type));
			}
			catch(...)
			{
				OnDisconnect();
			}
		}
	}

	void AddRecivedHandler(HandlerType handler)
	{
		recivedPacket.connect(handler);
	}

	void RemoveRecivedHandler(HandlerType handler)
	{
		recivedPacket.disconnect(handler);
	}

	void AddDisconnectHandler(DisconnectedHandlerType handler)
	{
		disconnected.connect(handler);
	}

	void RemoveDisconnectHandler(DisconnectedHandlerType handler)
	{
		disconnected.disconnect(handler);
	}

	std::string Name;
private:
	EventSerilizer<TList> serilizer;

	std::mutex socketMutex;
	std::thread m_thread;

	Simple_Socket client;
	bool isOpen = false;

	boost::signals2::signal<void (ClientInfo<TList>*, TVariant)> recivedPacket;
	boost::signals2::signal<void (ClientInfo<TList>*)> disconnected;

	void OnDisconnect()
	{
		std::unique_lock<std::mutex> lock(socketMutex, std::try_to_lock);
		if(isOpen)
		{
			isOpen = false;
			disconnected(this);
		}
	}

	void threadRun()
	{
		while(client.IsOpen())
		{
			try
			{
				auto packet = client.read();
				if(packet->Size()>0)
				{
					TVariant var = serilizer.deserilize(packet);
					recivedPacket(this, var);
				}
				else
				{
					OnDisconnect();
				}
			}
			catch(...)
			{
				OnDisconnect();
			}
		}
	}


};

#endif /* defined(__ac__clientInfo__) */
