
#ifndef SERVER_H_
#define SERVER_H_

#include <cstdint>
#include "Network/NetSocket.h"
#include "Network/clientInfo.h"
#include "roomHandler.h"
#include "clientHandler.h"


class server {
public:
	server(uint port);
	~server();

private:
	Simple_Server listenServer;
	std::thread AcceptThread;
	ClientHandler clientHandler;
	bool running = true;
	uint port;


	void ThreadAcceptClient();

};

#endif /* SERVER_H_ */
