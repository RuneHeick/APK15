/*
 * statechart.cpp
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#include "statechart.h"

#include <exception>

namespace state
{

StateSelectMode::StateSelectMode(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg(Cli::LOGTYPE_INFO,"Enter SelectMode.");

	// Request mode from user:
	bool inputAccepted = false;
	do {
		std::string usrInput = Cli::getUserString("Choose \"server\" or \"client\"");

		if(usrInput.compare("server") == 0) { // 0 = equal
			post_event(EvServerMode());
			inputAccepted = true;
		} else if(usrInput.compare("client") == 0) {
			post_event(EvClientMode());
			inputAccepted = true;
		} else {
			Cli::writeChatMsg(Cli::LOGTYPE_ERROR, std::string("Unknown input: ") + usrInput);
		}
	} while (!inputAccepted);
}

int RequestPort() // todo fri funktion - syntes vi det er en god ide????
{
	int port;
	bool inputAccepted = false;
	do {
		try {
			port = Cli::getUserInt("Set the port:");
		} catch(...) {
			continue;
		}

		if(port > 0 && port <= 65535) {
			inputAccepted = true;
		} else {
			Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Port out of range. Valid interval: [0,65535].");
		}
	} while (!inputAccepted);

	return port;
}

StateServerSetup::StateServerSetup(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg(Cli::LOGTYPE_INFO,"Enter StateServerSetup.");

	int port = RequestPort();

	context<StateServer>().chatServer.SetPort(port);
}

StateClientDisconnected::StateClientDisconnected(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg(Cli::LOGTYPE_INFO,"Enter StateClientDisconnected.");

	// Request ip from user:
	std::string ip = Cli::getUserString("Set the server ip:");

	// Request port from user:
	int port = RequestPort();

	context<StateClient>().chatClient.Connect(ip, port);
}

} // end namespace state
