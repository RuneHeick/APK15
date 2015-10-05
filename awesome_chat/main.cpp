
#include <iostream>
#include <thread>

#include "clientInfo.h"
#include "StateMachine/StateMachineWrapper.h"
#include "event.h"
#include "eventJoin.h"
#include "eventWho.h"
#include "eventMsg.h"

#include "clientInfo.h"
#include "NetSocket.h"
#include "EventSerilizer.h"
#include "messageParser.h"

bool running = true;
//Init The Variant Type;
typedef ImplemToList<Interface>::type IList;

void EccoServer()
{
	Simple_Server server;
	server.Lisen(5555);
	std::cout<<"Server Started"<<std::endl;
	while(running)
	{
		std::cout<<"Accepting"<<std::endl;
		Simple_Socket user = server.Accept();
		std::cout<<"Got Client"<<std::endl;
		while(user.IsOpen())
		{
			user.write(user.read());
		}
	}
}



int main(){
//    MessageParser mp;
//    mp.createEventFromInput<ClientInfo<IList>::TVariant>("Rune", "hej med jer");
//    mp.createEventFromInput<ClientInfo<IList>::TVariant>("Henrik", "/who");
//    mp.createEventFromInput<ClientInfo<IList>::TVariant>("Rahlff", "/join IHA");
    
//	std::thread t1(EccoServer);
//
//	usleep(10000);

    EventSerilizer<IList> ser;
//	Simple_Socket c;
//	c.connect("localhost",5555);
//	std::cout<<"Socket connected"<<std::endl;
//	ClientInfo<IList> ci( c );
//	std::cout<<"Client Info created"<<std::endl;
//	EventSerilizer<IList> serilizer;
//	std::shared_ptr<RawPacket> packet = serilizer.serilize(EventJoin());
//
//	EventJoin rune;
//	ClientInfo<IList>::TVariant var = rune;
//
//	std::cout<<"Sending"<<std::endl;
//	ci.Send(var);
//
//
//	usleep(10000);
//
//	c.disconnect();
//	running = false;
//	t1.join();

	return 0;
	// Create and initiate the state machine
//	StateMachine::StateMachineWrapper statemachine;

	// Function pointer to handle input
	std::function<void(const std::shared_ptr<std::string>&)> inputHandlerFunc = std::bind(&StateMachine::StateMachineWrapper::HandleUserInput, &statemachine, std::placeholders::_1);
	bool stopLoop = false;

	// Start reading user intput
//	UserInputHandler uih( std::bind(&StateMachine::StateMachineWrapper::HandleUserInput, &statemachine, std::placeholders::_1) );
//	uih.Start();


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

//	const std::chrono::seconds sleepTime_s(90);
//	std::this_thread::sleep_for(sleepTime_s);
//
//	Cli::writeDebugMsg(">> main exit <<");
}

