
#include "server.h"
#include "cli.h"

server::server(uint serverPort): port(serverPort) {
	listenServer.Lisen(port);
	AcceptThread = std::thread(std::bind(&server::ThreadAcceptClient, this));
}

server::~server() {
	running = false;
	try
	{
		Simple_Socket CloseConnection;
		CloseConnection.connect("localhost", port);
		CloseConnection.disconnect();
		AcceptThread.join();
	}
	catch(...)
	{};
}

void server::ThreadAcceptClient()
{
	Cli::writeDebugMsg("Accept thread is starting");
	while(running)
	{
		std::shared_ptr<ClientInfo> client;
		try
		{
			Simple_Socket clientConnection = listenServer.Accept();
			client = std::shared_ptr<ClientInfo>(new ClientInfo(clientConnection));
		}
		catch(...)
		{
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Connection faild for some reson");
		}

		if(client)
		{
			clientHandler.addNewClient(client);
		}
	}
}
