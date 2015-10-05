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
		context<StateClientDisconnected>().port = port;

		try
		{
			context<StateClient>().chatClient.connect(context<StateClientDisconnected>().ip ,port);
		}
		catch(...)
		{
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to connect to server (ip: "+context<StateClientDisconnected>().ip+" port: "+std::to_string(port)+" )");
			return  transit<StateClientDisconnected>();
		}

		post_event(EvClientConnect());
	} catch(...) {
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");

}

	return discard_event();
}

} /* namespace StateMachine */
