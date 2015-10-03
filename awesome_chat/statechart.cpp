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
		Cli::writeChatMsg(Cli::LOGTYPE_INFO, "Choose \"server\" or \"client\"");
		std::string usrInput = Cli::getUserInput();

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

StateServerSetup::StateServerSetup(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg(Cli::LOGTYPE_INFO,"Enter StateServerSetup.");

	int port;

	// Request port from user:
	bool inputAccepted = false;
	do {
		Cli::writeChatMsg(Cli::LOGTYPE_INFO, "Set the port:");
		std::string usrInput = Cli::getUserInput();

		try {
			port = std::stoi(usrInput);
		} catch(std::out_of_range& e) {
			Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Port out of range. Valid interval: [0,65535].");
			continue;
		} catch(std::invalid_argument& e) {
			Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Invalid input - unable to convert to a number.");
			continue;
		}

		if(port > 0 && port <= 65535) {
			inputAccepted = true;
		} else {
			Cli::writeChatMsg(Cli::LOGTYPE_ERROR, "Port out of range. Valid interval: [0,65535].");
		}

	} while (!inputAccepted);

	context<StateServer>().chatServer.SetPort(port);
}



} // end namespace state
