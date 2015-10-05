/*
 * StateServerRunning.h
 */

#ifndef STATEMACHINE_STATESERVERRUNNING_H_
#define STATEMACHINE_STATESERVERRUNNING_H_

#include "StateServer.h"

namespace StateMachine {


struct StateServerRunning : sc::simple_state<StateServerRunning, StateServer>
{
	typedef sc::transition<EvError, StateServerSetup> reactions;
	StateServerRunning() { Cli::writeDebugMsg("Enter StateServerRunning."); }
	~StateServerRunning() { Cli::writeDebugMsg("Exit StateServerRunning."); }
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESERVERRUNNING_H_ */
