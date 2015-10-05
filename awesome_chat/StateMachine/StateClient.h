/*
 * StateClient.h
 */

#ifndef STATEMACHINE_STATECLIENT_H_
#define STATEMACHINE_STATECLIENT_H_

#include "ChatStateMachine.h"
#include "../Network/NetSocket.h"

namespace StateMachine {

struct StateClient : sc::simple_state<StateClient, ChatStateMachine, StateClientDisconnected>
{
	StateClient() { Cli::writeDebugMsg("Enter StateClient."); }
	~StateClient() { Cli::writeDebugMsg("Exit StateClient."); }

	Simple_Socket chatClient;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENT_H_ */
