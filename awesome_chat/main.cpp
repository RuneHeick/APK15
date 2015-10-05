
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



//	std::thread t1(EccoServer);
//
//	usleep(10000);
//
//	Simple_Socket c;
//	c.connect("localhost",5555);
//	std::cout<<"Socket connected"<<std::endl;
//	ClientInfo<IList> ci( c );
//	std::cout<<"Client Info created"<<std::endl;
//	EventSerilizer<IList> serilizer;
//	std::shared_ptr<RawPacket> packet = serilizer.serilize(Join());
//
//	Join rune;
//	ClientInfo<IList>::TVariant var = rune;
//
//	std::cout<<"Sending"<<std::endl;
//	ci.Send(var);
//
//
//	usleep(10000);
//
//	running = false;
//	c.disconnect();
//	t1.join();

	// Create and initiate the state machine
	StateMachine::StateMachineWrapper statemachine;

	// Function pointer to handle input
	std::function<void(const std::shared_ptr<std::string>&)> inputHandlerFunc = std::bind(&StateMachine::StateMachineWrapper::HandleUserInput, &statemachine, std::placeholders::_1);
	bool stopLoop = false;

	// Start reading user intput
	const std::chrono::milliseconds sleepTime_ms(10);
	while(!stopLoop)	{
		std::shared_ptr<std::string> usrInput = std::make_shared<std::string>(Cli::getUserInput());
		if((*usrInput).compare("/exit") == 0) {
			stopLoop = true;
		} else {
			if(inputHandlerFunc)
				inputHandlerFunc(usrInput);
		}

		std::this_thread::sleep_for(sleepTime_ms);
	}
	Cli::writeDebugMsg(">> main exit <<");
}

