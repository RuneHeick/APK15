/*
 * StateSelectMode.cpp
 */

#include "StateSelectMode.h"

#include "StateServer.h"
#include "StateServerSetup.h"
#include "StateClient.h"
#include "StateClientDisconnected.h"
#include "StateClientGetIp.h"

namespace StateMachine {

StateSelectMode::StateSelectMode(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter SelectMode.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Choose \"server\" or \"client\""));
}

StateSelectMode::~StateSelectMode() {
	Cli::writeDebugMsg("Exit SelectMode.");
}

sc::result StateSelectMode::react( const EvUserInput & event ) {
	if(event.userInput.compare("server") == 0) { // 0 = equal
		post_event(EvServerMode());
	} else if(event.userInput.compare("client") == 0) {
		post_event(EvClientMode());
	} else {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, std::string("Unknown input: ") + event.userInput);
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Choose \"server\" or \"client\""));
	}

	return discard_event();
}

} /* namespace StateMachine */
