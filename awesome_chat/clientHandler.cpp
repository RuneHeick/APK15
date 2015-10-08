/*
 * clientHandler.cpp
 */

#include "clientHandler.h"

#include "cli.h"

const std::string DEFAULT_ROOM_NAME("Lobby");

ClientHandler::ClientHandler() : roomHandler(DEFAULT_ROOM_NAME) {
}

ClientHandler::~ClientHandler() {
}

void ClientHandler::addNewClient(std::shared_ptr<ClientInfo> newClient_ptr)
{
	Cli::writeDebugMsg("Adding new client");
	MapEntry mapEntry;
	mapEntry.client_ptr = newClient_ptr;
	mapEntry.conReceiveNetworkEvent = newClient_ptr->recivedPacket.connect(boost::bind(&ClientHandler::OnReceivedNetworkEvent, boost::ref(*this), _1, _2));
	mapEntry.conDisconnect = newClient_ptr->disconnected.connect(boost::bind(&ClientHandler::OnDisconnect, boost::ref(*this), _1));
	mapEntry.name_ptr = std::shared_ptr<std::string>( new std::string("NewClient") );

	try {
		std::lock_guard<std::mutex> lock(mtx);
		mapEntry.room_ptr = roomHandler.getRoom(DEFAULT_ROOM_NAME);
		mapEntry.room_ptr->addClient(newClient_ptr);
		m_ClientToRoomMap.insert( std::make_pair(NonDeRefPtr(newClient_ptr.get()), mapEntry) );
		Cli::writeDebugMsg("New client added by ClientHandler");
	} catch (...) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Failed to add client");
		// todo What to do??
	}
}

void ClientHandler::OnReceivedNetworkEvent(ClientInfo const & client, EventVariant event)
{
	Cli::writeDebugMsg("Handling event from client");
	auto bound_visitor = std::bind(ServerMessageVisitor(), boost::ref(*this), std::placeholders::_1, boost::ref(client));
	boost::apply_visitor(bound_visitor, event);
}

void ClientHandler::OnDisconnect(ClientInfo const & client)
{
	Cli::writeDebugMsg("Disconnecting client");
	try {
		std::lock_guard<std::mutex> lock(mtx);

		auto itr = m_ClientToRoomMap.find( (void*)&client );
		if(itr != m_ClientToRoomMap.end()) {
			// Disconnect signals
			itr->second.conDisconnect.disconnect();
			itr->second.conReceiveNetworkEvent.disconnect();

			// Remove client from room and destroy room if it is empty
			itr->second.room_ptr->removeClient(itr->second.client_ptr); // seconed = MapEntry
			std::string roomName_str = itr->second.room_ptr->getName();
			if( itr->second.room_ptr->isEmpty() ) {
				roomHandler.deleteRoom(roomName_str);
				Cli::writeDebugMsg("Deleted room " + roomName_str );
			}

			// Remove client from map:
			std::string clientName_str(*itr->second.name_ptr);
			m_ClientToRoomMap.erase(itr);
			Cli::writeDebugMsg(clientName_str + " disconnected");
		} else {
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to find client in map");
		}
	} catch (...) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Failed to remove client.");
	}
}

void ClientHandler::HandleEvent(EventJoin& event, ClientInfo const & client) {
	Cli::writeDebugMsg("Handling join event");
	std::lock_guard<std::mutex> lock(mtx);

	// find client
	auto itr = m_ClientToRoomMap.find( (void*)&client );
	if(itr == m_ClientToRoomMap.end()) { // Make sure it returned something
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable find client in map");
		// todo skal der kastes en exception her?
		return;
	}

	try {
		// Set new name
		*itr->second.name_ptr = event.getUser();

		// Change room if different:
		std::shared_ptr<Room> newRoom_ptr = roomHandler.getRoom(event.getTargetRoom());
		if( itr->second.room_ptr != newRoom_ptr ) {
			// Move to new room:
			itr->second.room_ptr->removeClient(itr->second.client_ptr);
			itr->second.room_ptr = newRoom_ptr;
			itr->second.room_ptr->addClient(itr->second.client_ptr);
		}

		EventMsg eventMsg("Server", *itr->second.name_ptr + std::string(" joined ") + itr->second.room_ptr->getName());
		itr->second.room_ptr->broadcastMsg(eventMsg);
	}catch (...) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Exception during Join update");
	}
}

void ClientHandler::HandleEvent(EventMsg& event, ClientInfo const & client) {
	Cli::writeDebugMsg("Handling Msg event");
	std::lock_guard<std::mutex> lock(mtx);

	auto itr = m_ClientToRoomMap.find( (void*)&client );
	if(itr != m_ClientToRoomMap.end()) {
		try {
			EventMsg e_msg(*itr->second.name_ptr, event.getMessage());
			itr->second.room_ptr->broadcastMsg(e_msg);
		} catch (...) {
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Failed to create msg event for broadcast");
			return;
		}
	} else {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to find client in map");
		// todo skal der kastes en exception her?
	}
}

void ClientHandler::HandleEvent(EventWho& event, ClientInfo const & client) {
	// todo try catch
	Cli::writeDebugMsg("Handling Who event");
	std::lock_guard<std::mutex> lock(mtx);

	auto itrRqClient = m_ClientToRoomMap.find( (void*)&client ); // Find iterator for requesting client
	if(itrRqClient == m_ClientToRoomMap.end()) { // Make sure it returned something
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable find client in map");
		// todo skal der kastes en exception her?
		return;
	}

	try {
		std::string clients_str("Room " + itrRqClient->second.room_ptr->getName() + " contains: ");

		// Iterate through the list clients in the room and add names to the string:
		for(auto itList = itrRqClient->second.room_ptr->clients_.begin(); itList != itrRqClient->second.room_ptr->clients_.end(); itList++) {
			auto itrClientN = m_ClientToRoomMap.find( (void*)(*itList).get() ); // Find iterator to client n in the room.
			clients_str.append(*itrClientN->second.name_ptr);
			clients_str.append(",");
		}

		// Send message event with the result:
		EventMsg e_msg("Server", clients_str);
		EventVariant eventOut = e_msg;
		itrRqClient->second.client_ptr->Send(eventOut);
	} catch (...) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Exception: Creating or transmitting who response");
	}
}
