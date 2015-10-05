/*
 * StateServerSetup.cpp
 */

#include "StateServerSetup.h"

#include "StateServerRunning.h"
#include "StateHelperFunctions.h"

namespace StateMachine {

StateServerSetup::StateServerSetup(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter StateServerSetup.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");
}

sc::result StateServerSetup::react( const EvSetupDone & ) {
	return  transit<StateServerRunning>();
}

sc::result StateServerSetup::react( const EvUserInput & ) {
	uint16_t port;
	try {
		port = ParsePort(*context<ChatStateMachine>().usrInput);
		context<StateServer>().port = port;
		post_event(EvSetupDone());
	} catch(...) {
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");
	}

	return discard_event();
}

} /* namespace StateMachine */
