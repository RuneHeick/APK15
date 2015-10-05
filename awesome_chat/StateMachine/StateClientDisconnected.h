/*
 * StateClientDisconnected.h
 */

#ifndef STATEMACHINE_STATECLIENTDISCONNECTED_H_
#define STATEMACHINE_STATECLIENTDISCONNECTED_H_

#include "StateClient.h"
#include "../NetSocket.h"

namespace StateMachine {

struct StateClientDisconnected : sc::simple_state<StateClientDisconnected, StateClient, StateClientGetIp>
{
	StateClientDisconnected()
	{
		Cli::writeDebugMsg("Enter StateClientDisconnected.");
		context<StateClient>().chatClient = Simple_Socket();
	}

	~StateClientDisconnected() { Cli::writeDebugMsg("Exit StateClientDisconnected."); }

	std::string ip;
	uint port;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTDISCONNECTED_H_ */
