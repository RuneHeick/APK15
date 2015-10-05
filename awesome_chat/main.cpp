
#include <iostream>
#include <thread>

#include "clientInfo.h"
#include "StateMachine/StateMachineWrapper.h"
#include "UserInputHandler.h"
#include "event.h"
#include "eventJoin.h"

#include "clientInfo.h"
#include "NetSocket.h"
#include "EventSerilizer.h"

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



	std::thread t1(EccoServer);

	usleep(10000);

	Simple_Socket c;
	c.connect("localhost",5555);
	std::cout<<"Socket connected"<<std::endl;
	ClientInfo<IList> ci( c );
	std::cout<<"Client Info created"<<std::endl;
	EventSerilizer<IList> serilizer;
	std::shared_ptr<RawPacket> packet = serilizer.serilize(EventJoin());

	EventJoin rune;
	ClientInfo<IList>::TVariant var = rune;

	std::cout<<"Sending"<<std::endl;
	ci.Send(var);


	usleep(10000);

	c.disconnect();
	running = false;
	t1.join();

	return 0;
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

