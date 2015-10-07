/*
 * StateClient.h
 */

#ifndef STATEMACHINE_STATECLIENT_H_
#define STATEMACHINE_STATECLIENT_H_

#include "ChatStateMachine.h"
#include "../messageParser.h"

namespace StateMachine {

struct StateClient : sc::simple_state<StateClient, ChatStateMachine, StateClientDisconnected>
{
	StateClient() { Cli::writeDebugMsg("Enter StateClient."); }
	~StateClient() { Cli::writeDebugMsg("Exit StateClient."); }

	std::string ip = "";
	uint port = 0;
	MessageParser inputParser;

};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENT_H_ */
