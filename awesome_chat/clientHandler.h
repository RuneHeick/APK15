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

class ClientHandler {
public:
	ClientHandler();

	void addNewClient(std::shared_ptr<ClientInfo> newClient);

	virtual ~ClientHandler();

private:
	RoomHandler handler;

};

#endif /* CLIENTHANDLER_H_ */
