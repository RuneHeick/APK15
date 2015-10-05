/*
 * StateClientDisconnected.h
 */

#ifndef STATEMACHINE_STATECLIENTDISCONNECTED_H_
#define STATEMACHINE_STATECLIENTDISCONNECTED_H_

#include "StateClient.h"

namespace StateMachine {

struct StateClientDisconnected : sc::simple_state<StateClientDisconnected, StateClient, StateClientGetIp>
{
	StateClientDisconnected() { Cli::writeDebugMsg("Enter StateClientDisconnected."); }
	~StateClientDisconnected() { Cli::writeDebugMsg("Exit StateClientDisconnected."); }
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTDISCONNECTED_H_ */
