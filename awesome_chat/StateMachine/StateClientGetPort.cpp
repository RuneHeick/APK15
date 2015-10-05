/*
 * StateClientGetPort.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: stud
 */

#include "StateClientGetPort.h"

#include "StateClientConnected.h"
#include "StateHelperFunctions.h"


namespace StateMachine {

StateClientGetPort::StateClientGetPort(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter StateClientGetPort.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");
}

//StateClientGetPort::~StateClientGetPort() {
//	// TODO Auto-generated destructor stub
//}

sc::result StateClientGetPort::react( const EvClientConnect & ) {
	return  transit<StateClientConnected>();
}

sc::result StateClientGetPort::react( const EvUserInput & )
{
	uint16_t port;
	try {
		port = ParsePort(*context<ChatStateMachine>().usrInput);
		context<StateClient>().chatClient.SetPort(port);
		post_event(EvClientConnect());
	} catch(...) {
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the port:");
}

	return discard_event();
}

} /* namespace StateMachine */
