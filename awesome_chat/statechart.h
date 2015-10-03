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
#include <boost/statechart/transition.hpp>

#include "cli.h"

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

struct StateSelectMode : sc::simple_state<StateSelectMode, ChatStateMachine>
{
	typedef boost::mpl::list<sc::transition<EvServerMode, StateServer>,
			sc::transition<EvClientMode, StateClient> >reactions;

	StateSelectMode() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter SelectMode."); }
	~StateSelectMode() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit SelectMode."); }
};

struct StateServer : sc::simple_state<StateServer, ChatStateMachine, StateServerSetup>
{
	StateServer() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateServer."); }
	~StateServer() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateServer."); }
};

struct StateServerRunning : sc::simple_state<StateServerRunning, StateServer>
{
	typedef sc::transition<EvError, StateServerSetup> reactions;
	StateServerRunning() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateServerRunning."); }
	~StateServerRunning() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateServerRunning."); }
};

struct StateServerSetup : sc::simple_state<StateServerSetup, StateServer>
{
	typedef sc::transition<EvSetupDone, StateServerRunning> reactions;
	StateServerSetup() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateServerSetup."); }
	~StateServerSetup() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateServerSetup."); }
};

struct StateClient : sc::simple_state<StateClient, ChatStateMachine, StateClientDisconnected>
{
	StateClient() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateClient."); }
	~StateClient() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateClient."); }
};

struct StateClientConnected : sc::simple_state<StateClientConnected, StateClient, StateLobby>
{
	typedef sc::transition<EvClientDisconnect, StateClientDisconnected> reactions;
	StateClientConnected() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateClientConnected."); }
	~StateClientConnected() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateClientConnected."); }
};

struct StateClientDisconnected : sc::simple_state<StateClientDisconnected, StateClient>
{
	typedef sc::transition<EvClientConnect, StateClientConnected> reactions;
	StateClientDisconnected() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateClientDisconnected."); }
	~StateClientDisconnected() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateClientDisconnected."); }
};

struct StateRoom : sc::simple_state<StateRoom, StateClientConnected>
{
	typedef sc::transition<EvClientLeaveRoom, StateLobby> reactions;
	StateRoom() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateRoom."); }
	~StateRoom() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateRoom."); }
};

struct StateLobby : sc::simple_state<StateLobby, StateClientConnected>
{
	typedef sc::transition<EvClientEnterRoom, StateRoom> reactions;
	StateLobby() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Enter StateLobby."); }
	~StateLobby() { cli.writeDebugMsg(cli.LOGTYPE_INFO,"Exit StateLobby."); }
};

} // end namespace state

#endif /* STATECHART_H_ */
