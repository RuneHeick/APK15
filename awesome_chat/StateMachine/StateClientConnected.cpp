/*
 * StateClientConnected.cpp
 */

#include "StateClientConnected.h"

#include "StateClientDisconnected.h"
#include "StateClientGetIp.h" // todo why is this needed?

namespace StateMachine {

sc::result StateClientConnected::react( const EvClientDisconnect & ) {
	return transit<StateClientDisconnected>();
}

sc::result StateClientConnected::react( const EvUserInput & userEvent ) {


	EventVariant event;
	try
	{
		event = context<StateClient>().inputParser.createEventFromInput("",userEvent.userInput);
	}
	catch(...)
	{
		Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Bad Input");
		return discard_event();
	}

	try
	{
		m_client->Send(event);
	}
	catch(...)
	{
		return transit<StateClientDisconnected>();
	}

	return discard_event();
}


} /* namespace StateMachine */
