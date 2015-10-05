/*
 * StateClientGetPort.h
 */

#ifndef STATEMACHINE_STATECLIENTGETPORT_H_
#define STATEMACHINE_STATECLIENTGETPORT_H_

#include "StateClientDisconnected.h"

namespace StateMachine {

struct StateClientGetPort : sc::state<StateClientGetPort, StateClientDisconnected>
{
	typedef boost::mpl::list<
			sc::custom_reaction<EvClientConnect>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientGetPort(my_context ctx);
	~StateClientGetPort() { Cli::writeDebugMsg("Exit StateClientGetPort."); }

	sc::result react( const EvClientConnect & );
	sc::result react( const EvUserInput & );
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTGETPORT_H_ */
