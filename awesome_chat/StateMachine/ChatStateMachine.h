/*
 * BoostStateMachine.h
 */

#ifndef STATEMACHINE_CHATSTATEMACHINE_H_
#define STATEMACHINE_CHATSTATEMACHINE_H_

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>

#include "../cli.h"

namespace StateMachine {

namespace sc = boost::statechart;

struct EvServerMode : sc::event<EvServerMode> {};
struct EvClientMode : sc::event<EvClientMode> {};
struct EvError : sc::event<EvError> {};
struct EvSetupDone : sc::event<EvSetupDone> {};
struct EvClientConnect : sc::event<EvClientConnect> {};
struct EvClientDisconnect : sc::event<EvClientDisconnect> {};
struct EvClientIpDone : sc::event<EvClientIpDone> {};
struct EvUserInput : sc::event<EvUserInput> {};

// States forward declarations
struct StateSelectMode;
struct StateServer;
struct StateClient;
struct StateServerSetup;
struct StateClientDisconnected;
struct StateClientGetIp;

struct ChatStateMachine  : sc::state_machine<ChatStateMachine, StateSelectMode>
{
	std::shared_ptr<std::string> usrInput;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_CHATSTATEMACHINE_H_ */
