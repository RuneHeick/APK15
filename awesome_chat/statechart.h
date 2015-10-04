/*
 * statechart.h
 *
 *  Created on: Oct 3, 2015
 *      Author: stud
 */

#ifndef STATECHART_H_
#define STATECHART_H_

#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>

#include "cli.h"
#include "server.h"
#include "client.h"

namespace state
{

namespace sc = boost::statechart;

// Events:
struct EvServerMode : sc::event<EvServerMode> {};
struct EvClientMode : sc::event<EvClientMode> {};
struct EvError : sc::event<EvError> {};
struct EvSetupDone : sc::event<EvSetupDone> {};
struct EvClientConnect : sc::event<EvClientConnect> {};
struct EvClientDisconnect : sc::event<EvClientDisconnect> {};
struct EvClientEnterRoom : sc::event<EvClientEnterRoom> {};
struct EvClientLeaveRoom : sc::event<EvClientLeaveRoom> {};


// States forward declarations
struct StateSelectMode;
struct StateServer;
struct StateClient;
struct StateServerSetup;
struct StateClientDisconnected;
struct StateLobby;


// State machine
struct ChatStateMachine : sc::state_machine<ChatStateMachine, StateSelectMode> {};

// States:

struct StateSelectMode : sc::state<StateSelectMode, ChatStateMachine>
{
	typedef boost::mpl::list<sc::transition<EvServerMode, StateServer>,
			sc::transition<EvClientMode, StateClient> >reactions;

	StateSelectMode(my_context ctx);
	~StateSelectMode() { Cli::writeDebugMsg("Exit SelectMode."); }
};

struct StateServer : sc::simple_state<StateServer, ChatStateMachine, StateServerSetup>
{
	StateServer() { Cli::writeDebugMsg("Enter StateServer."); }
	~StateServer() { Cli::writeDebugMsg("Exit StateServer."); }

	server chatServer;
};

struct StateServerRunning : sc::simple_state<StateServerRunning, StateServer>
{
	typedef sc::transition<EvError, StateServerSetup> reactions;
	StateServerRunning() { Cli::writeDebugMsg("Enter StateServerRunning."); }
	~StateServerRunning() { Cli::writeDebugMsg("Exit StateServerRunning."); }
};

struct StateServerSetup : sc::state<StateServerSetup, StateServer>
{
	typedef sc::transition<EvSetupDone, StateServerRunning> reactions;
	StateServerSetup(my_context ctx);
	~StateServerSetup() { Cli::writeDebugMsg("Exit StateServerSetup."); }
};

struct StateClient : sc::simple_state<StateClient, ChatStateMachine, StateClientDisconnected>
{
	StateClient() { Cli::writeDebugMsg("Enter StateClient."); }
	~StateClient() { Cli::writeDebugMsg("Exit StateClient."); }

	client chatClient;
};

struct StateClientConnected : sc::simple_state<StateClientConnected, StateClient, StateLobby>
{
	typedef sc::transition<EvClientDisconnect, StateClientDisconnected> reactions;
	StateClientConnected() { Cli::writeDebugMsg("Enter StateClientConnected."); }
	~StateClientConnected() { Cli::writeDebugMsg("Exit StateClientConnected."); }
};

struct StateClientDisconnected : sc::state<StateClientDisconnected, StateClient>
{
	typedef sc::transition<EvClientConnect, StateClientConnected> reactions;
	StateClientDisconnected(my_context ctx);
	~StateClientDisconnected() { Cli::writeDebugMsg("Exit StateClientDisconnected."); }
};

struct StateRoom : sc::simple_state<StateRoom, StateClientConnected>
{
	typedef sc::transition<EvClientLeaveRoom, StateLobby> reactions;
	StateRoom() { Cli::writeDebugMsg("Enter StateRoom."); }
	~StateRoom() { Cli::writeDebugMsg("Exit StateRoom."); }
};

struct StateLobby : sc::simple_state<StateLobby, StateClientConnected>
{
	typedef sc::transition<EvClientEnterRoom, StateRoom> reactions;
	StateLobby() { Cli::writeDebugMsg("Enter StateLobby."); }
	~StateLobby() { Cli::writeDebugMsg("Exit StateLobby."); }
};

} // end namespace state

#endif /* STATECHART_H_ */
