/*
 * StateClientGetIp.h
 */

#ifndef STATEMACHINE_STATECLIENTGETIP_H_
#define STATEMACHINE_STATECLIENTGETIP_H_

#include "StateClientDisconnected.h"

namespace StateMachine {

struct StateClientGetIp : sc::state<StateClientGetIp, StateClientDisconnected>
{
	typedef sc::custom_reaction<EvUserInput> reactions;

	StateClientGetIp(my_context ctx);
	~StateClientGetIp() { Cli::writeDebugMsg("Exit StateClientGetIp."); }

	sc::result react( const EvUserInput & );
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTGETIP_H_ */
