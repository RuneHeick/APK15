/*
 * StateClientConnected.cpp
 */

#include "StateClientConnected.h"

#include "StateClientDisconnected.h"
#include "StateClientGetIp.h" // todo why is this needed?

namespace StateMachine {

sc::result StateClientConnected::react( const EvClientDisconnect & ) {
	return transit<StateClientDisconnected>();
}

sc::result StateClientConnected::react( const EvUserInput & ) {
	/*auto event =*/ context<StateClient>().chatClient.ParseUserInput(*context<ChatStateMachine>().usrInput);
	// todo handle event
	// if(event == message??? ) {
	//	Cli::writeChatMsg(event.user, event.msg);

	return discard_event();
}

} /* namespace StateMachine */
