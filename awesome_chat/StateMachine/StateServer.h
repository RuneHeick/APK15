/*
 * StateServer.h
 */

#ifndef STATEMACHINE_STATESERVER_H_
#define STATEMACHINE_STATESERVER_H_

#include "ChatStateMachine.h"
#include "../server.h"

namespace StateMachine {

struct StateServer : sc::simple_state<StateServer, ChatStateMachine, StateServerSetup>
{
	StateServer() { Cli::writeDebugMsg("Enter StateServer."); port = 0; }
	~StateServer() { Cli::writeDebugMsg("Exit StateServer."); }

	uint port;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESERVER_H_ */
