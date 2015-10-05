/*
 * StateSelectMode.cpp
 */

#include "StateSelectMode.h"

#include "StateServer.h"
#include "StateServerSetup.h" // todo why???
#include "StateClient.h"
#include "StateClientDisconnected.h" // Todo why???
#include "StateClientGetIp.h" // todo why???

namespace StateMachine {

StateSelectMode::StateSelectMode(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter SelectMode.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Choose \"server\" or \"client\""));
}

StateSelectMode::~StateSelectMode() {
	Cli::writeDebugMsg("Exit SelectMode.");
}

sc::result StateSelectMode::react( const EvServerMode & ) {
	return transit<StateServer>();
}

sc::result StateSelectMode::react( const EvClientMode & ) {
	return transit<StateClient>();
}

sc::result StateSelectMode::react( const EvUserInput & ) {
	if((*context<ChatStateMachine>().usrInput).compare("server") == 0) { // 0 = equal
		post_event(EvServerMode());
	} else if((*context<ChatStateMachine>().usrInput).compare("client") == 0) {
		post_event(EvClientMode());
	} else {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, std::string("Unknown input: ") + (*context<ChatStateMachine>().usrInput));
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Choose \"server\" or \"client\""));
	}

	return discard_event();
}

} /* namespace StateMachine */
