/*
 * StateServerSetup.h
 */

#ifndef STATEMACHINE_STATESERVERSETUP_H_
#define STATEMACHINE_STATESERVERSETUP_H_

#include "StateServer.h"

namespace StateMachine {

struct StateServerSetup : sc::state<StateServerSetup, StateServer>
{
	typedef boost::mpl::list<
			sc::custom_reaction<EvSetupDone>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateServerSetup(my_context ctx);
	~StateServerSetup() { Cli::writeDebugMsg("Exit StateServerSetup."); }

	sc::result react( const EvSetupDone & );
	sc::result react( const EvUserInput & );
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESERVERSETUP_H_ */
