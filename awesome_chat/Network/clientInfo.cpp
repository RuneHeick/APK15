/*
* clientInfo.cpp
*
*  Created on: Oct 5, 2015
*      Author: stud
*/
#include "clientInfo.h"
#include "../cli.h"

ClientInfo::ClientInfo(Simple_Socket clientsocket): client(clientsocket)
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

void ClientInfo::Send(EventVariant& type)
{
	std::lock_guard<std::mutex> lock(socketMutex);
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

ClientInfo::~ClientInfo()
{
	Disconnect();
	m_thread.join();
	Cli::writeDebugMsg("Client Destructed");
}

void ClientInfo::Disconnect()
{
	client.disconnect();
	OnDisconnect();
}

void ClientInfo::OnDisconnect()
{
	std::unique_lock<std::mutex> lock(socketMutex, std::try_to_lock); // todo: http://stackoverflow.com/questions/14920997/should-unique-lock-with-try-to-lock-owns-the-mutex-even-if-lock-fails
	if(isOpen)
	{
		isOpen = false;
		disconnected(*this);
	}
}

void ClientInfo::threadRun()
{
	while(client.IsOpen())
	{
		try
		{
			auto packet = client.read();
			if(packet->Size()>0)
			{
				EventVariant var = serilizer.deserilize(packet);
				recivedPacket(*this, var);
			}
			else
			{
				OnDisconnect();
				break;
			}
		}
		catch(...)
		{
			OnDisconnect();
			break;
		}
	}
}
