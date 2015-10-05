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
#include "../event.h"
#include <mutex>
#include <thread>
#include "EventSerilizer.h"
#include <boost/system/system_error.hpp>

template<typename TList>
class ClientInfo {
public:


	typedef typename boost::make_variant_over<TList>::type TVariant;

	typedef  boost::signals2::signal<void (ClientInfo<TList>&, TVariant)> ReciveSignal;
	typedef  boost::signals2::signal<void (ClientInfo<TList>&)> DisconnectSignal;
	typedef  boost::function<void (ClientInfo<TList>&, TVariant)> ReciveFuc;
	typedef  boost::function<void (ClientInfo<TList>&)> DisconnectFuc;

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

	void Disconnect()
	{
		std::unique_lock<std::mutex> lock(socketMutex, std::try_to_lock);
		if(isOpen)
		{
			isOpen = false;
			client.disconnect();
		}
	}


	/* Help how to do this
	void AddRecivedHandler(const ReciveFuc& handler)
	{
		recivedPacket.connect(handler);
	}

	void RemoveRecivedHandler(const ReciveFuc& handler)
	{
		recivedPacket.disconnect(handler);
	}

	void AddDisconnectHandler(const DisconnectFuc& handler)
	{
		disconnected.connect(handler);
	}

	void RemoveDisconnectHandler(const DisconnectFuc& handler)
	{
		disconnected.disconnect(handler);
	}
	*/

	ReciveSignal recivedPacket;
	DisconnectSignal  disconnected;

	std::string Name;
private:
	EventSerilizer<TList> serilizer;

	std::mutex socketMutex;
	std::thread m_thread;

	Simple_Socket client;
	bool isOpen = false;



	void OnDisconnect()
	{
		std::unique_lock<std::mutex> lock(socketMutex, std::try_to_lock);
		if(isOpen)
		{
			isOpen = false;
			disconnected(*this);
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
					recivedPacket(*this, var);
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
