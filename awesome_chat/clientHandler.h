/*
 * clientHandler.h
 *
 *  Created on: Oct 7, 2015
 *      Author: stud
 */

#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_
#include "Network/clientInfo.h"
#include "room.h"
#include "roomHandler.h"

struct ServerMessageVisitor; //forward declaration

struct MapEntry {
	std::shared_ptr<ClientInfo> client_ptr;
	std::shared_ptr<Room> room_ptr;
	boost::signals2::connection conReceiveNetworkEvent;
	boost::signals2::connection conDisconnect;
	std::shared_ptr<std::string> name_ptr;
};

class NonDeRefPtr {
public:
	NonDeRefPtr(void const * ptr) : m_ptr(ptr) {} ;
    friend bool operator<( NonDeRefPtr const & lhs, NonDeRefPtr const & rhs ) { return lhs.m_ptr < rhs.m_ptr; } // Needed for map
    friend bool operator<( NonDeRefPtr const & lhs, void const * rhs ) { return lhs.m_ptr < rhs; }
    friend bool operator<( void const * lhs, const NonDeRefPtr & rhs ) { return lhs < rhs.m_ptr; }

private:
	const void * m_ptr;
};

class ClientHandler {
	friend ServerMessageVisitor;
public:
	ClientHandler();
	~ClientHandler();

	void addNewClient(std::shared_ptr<ClientInfo> newClient);

private:
	std::mutex mtx;
	RoomHandler roomHandler;

	std::map<NonDeRefPtr,  MapEntry> m_ClientToRoomMap;
	std::vector<std::shared_ptr<ClientInfo>> m_DisconnectedClients;

	void OnReceivedNetworkEvent(ClientInfo const & client, EventVariant event);
	void OnDisconnect(ClientInfo const & client);

	void HandleEvent(EventJoin& event, ClientInfo const & client);
	void HandleEvent(EventMsg& event, ClientInfo const & client);
	void HandleEvent(EventWho& event, ClientInfo const & client);

	void RemoveDisconnectedClients(); // thread function
	std::thread m_thread;
	volatile bool m_threadRun;
};

struct ServerMessageVisitor : boost::static_visitor<void>
{
	template<typename T>
	void operator()(ClientHandler& clientHandler, T& event, ClientInfo const & client) const
	{
		clientHandler.HandleEvent(event, client);
	}
};

#endif /* CLIENTHANDLER_H_ */
