/*
 * StateServerRunning.h
 */

#ifndef STATEMACHINE_STATESERVERRUNNING_H_
#define STATEMACHINE_STATESERVERRUNNING_H_

#include "StateServer.h"
#include "../Network/NetSocket.h"

namespace StateMachine {


struct StateServerRunning : sc::state<StateServerRunning, StateServer>
{
	typedef sc::transition<EvError, StateServerSetup> reactions;
	StateServerRunning(my_context ctx) : my_base( ctx )
	{
		Cli::writeDebugMsg("Enter StateServerRunning.");
		try
		{
			serverSocket.Lisen(context<StateServer>().port);

		}
		catch(...)
		{
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to start server on "+std::to_string(context<StateServer>().port));
			post_event(EvError());
		}

	}
	~StateServerRunning() { Cli::writeDebugMsg("Exit StateServerRunning."); }

private:
	Simple_Server serverSocket;

};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESERVERRUNNING_H_ */
