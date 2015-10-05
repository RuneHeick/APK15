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
#include "../Events/Events.hpp"
#include <mutex>
#include <thread>
#include "EventSerilizer.h"
#include <boost/system/system_error.hpp>

class ClientInfo {
	typedef  boost::signals2::signal<void (ClientInfo&, EventVariant)> ReciveSignal;
	typedef  boost::signals2::signal<void (ClientInfo&)> DisconnectSignal;
public:

	ClientInfo() = default;

	ClientInfo(Simple_Socket clientsocket);

	void Send(EventVariant& type);


	void Disconnect();



	ReciveSignal recivedPacket;
	DisconnectSignal  disconnected;

	std::string Name;
private:
	EventSerilizer<IList> serilizer;

	std::mutex socketMutex;
	std::thread m_thread;

	Simple_Socket client;
	bool isOpen = false;


	void OnDisconnect();
	void threadRun();

};

#endif /* defined(__ac__clientInfo__) */
