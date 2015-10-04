
#include <iostream>
#include <boost/asio.hpp>

#include "statechart.h"
#include "messageParser.h"

int main(){
	// Create and initiate the state machine
//	state::ChatStateMachine sm;
//	sm.initiate();

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
    
    MessageParser myParser;
    myParser.createEventFromInput("Hej");
    myParser.createEventFromInput("/join");
    myParser.createEventFromInput("/who");
    myParser.createEventFromInput("/Join");
    myParser.createEventFromInput("/Who");
    myParser.createEventFromInput("/jOin");
    myParser.createEventFromInput("/wHO");
    myParser.createEventFromInput("/noo");
    myParser.createEventFromInput("/");
    myParser.createEventFromInput("/a");
    myParser.createEventFromInput("\\");
    myParser.createEventFromInput("/dfsjfsdkfjdskjfk");
    myParser.createEventFromInput("fjjgdshfjdsfhsdkjfhdsjfhdsjkghjsdhgksdjghsdkjfhdsjkbgksdjghdsjkbgjdkshgdsjkghdsjkhgdskjghdskjg");
    myParser.createEventFromInput("");

	Cli::writeDebugMsg(">> main exit <<");
}

