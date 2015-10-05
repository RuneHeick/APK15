/*
 * StateClientGetPort.cpp
 */

#include "StateClientGetPort.h"

#include "StateClientConnected.h"
#include "StateHelperFunctions.h"
#include "StateClientGetIp.h"


namespace StateMachine {

StateClientGetPort::StateClientGetPort(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter StateClientGetPort.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");
}

sc::result StateClientGetPort::react( const EvClientConnect & ) {
	return  transit<StateClientConnected>();
}

sc::result StateClientGetPort::react( const EvUserInput & )
{
	uint16_t port;
	try {
		port = ParsePort(*context<ChatStateMachine>().usrInput);
		context<StateClient>().port = port;

		post_event(EvClientConnect());
	} catch(...) {
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");

}

	return discard_event();
}

} /* namespace StateMachine */
