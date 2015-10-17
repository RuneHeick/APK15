/*
 * StateSelectMode.h
 */

#ifndef STATEMACHINE_STATESELECTMODE_H_
#define STATEMACHINE_STATESELECTMODE_H_

#include "ChatStateMachine.h"

namespace StateMachine {

struct StateSelectMode : sc::state<StateSelectMode, ChatStateMachine>
{
	typedef boost::mpl::list<
			sc::transition<EvServerMode, StateServer>,
			sc::transition<EvClientMode, StateClient>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateSelectMode(my_context ctx);
	~StateSelectMode();

	sc::result react( const EvUserInput & );
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESELECTMODE_H_ */
