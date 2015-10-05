/*
 * StateClientConnected.h
 */

#ifndef STATEMACHINE_STATECLIENTCONNECTED_H_
#define STATEMACHINE_STATECLIENTCONNECTED_H_

#include "StateClient.h"

namespace StateMachine {

struct StateClientConnected : sc::simple_state<StateClientConnected, StateClient>
{
	typedef boost::mpl::list<
			sc::custom_reaction<EvClientDisconnect>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientConnected() { Cli::writeDebugMsg("Enter StateClientConnected."); }
	~StateClientConnected() { Cli::writeDebugMsg("Exit StateClientConnected."); }

	sc::result react( const EvClientDisconnect & );
	sc::result react( const EvUserInput & );
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTCONNECTED_H_ */
