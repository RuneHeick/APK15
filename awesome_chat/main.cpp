
#include <iostream>
#include "clientInfo.h"
#include "statechart.h"
#include "event.h"
#include "eventJoin.h"

#include "clientInfo.h"
#include "NetSocket.h"


int main(){

	//Init The Variant Type;
	typedef ImplemToList<Interface>::type IList;
	typedef boost::make_variant_over<IList>::type VariantType;

	ClientInfo<VariantType> Temp(Client());


	return 0;
	// Create and initiate the state machine
	state::ChatStateMachine sm;
	sm.initiate();

//    // Server
//    sm.process_event(state::EvServerMode());
//    sm.process_event(state::EvSetupDone());
//    sm.process_event(state::EvError());
//
//    // Client
//    sm.process_event(state::EvClientMode());
//    sm.process_event(state::EvClientConnect());
//    sm.process_event(state::EvClientEnterRoom());
//    sm.process_event(state::EvClientDisconnect());
//    sm.process_event(state::EvClientConnect());
//    sm.process_event(state::EvClientEnterRoom());
//    sm.process_event(state::EvClientLeaveRoom());

//	Cli::writeDebugMsg(Cli::LOGTYPE_INFO, ">> main exit <<");
}

