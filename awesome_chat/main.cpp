
#include <iostream>
#include "clientInfo.h"
#include "StateMachine/StateMachineWrapper.h"
#include "UserInputHandler.h"
#include "event.h"
#include "eventJoin.h"

#include "clientInfo.h"
#include "NetSocket.h"


int main(){

	//Init The Variant Type;
	typedef ImplemToList<Interface>::type IList;
	typedef boost::make_variant_over<IList>::type VariantType;

	ClientInfo<VariantType> Temp(Client());

	// Create and initiate the state machine
	StateMachine::StateMachineWrapper statemachine;

	// Start reading user intput
	UserInputHandler uih( std::bind(&StateMachine::StateMachineWrapper::HandleUserInput, &statemachine, std::placeholders::_1) );
	uih.Start();


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

	const std::chrono::seconds sleepTime_s(90);
	std::this_thread::sleep_for(sleepTime_s);

	Cli::writeDebugMsg(">> main exit <<");
}

