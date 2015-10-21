/*
 * StateServerRunning.h
 */

#ifndef STATEMACHINE_STATESERVERRUNNING_H_
#define STATEMACHINE_STATESERVERRUNNING_H_

#include "StateServer.h"
#include "../server.h"

namespace StateMachine {


struct StateServerRunning : sc::state<StateServerRunning, StateServer>
{
	typedef sc::transition<EvError, StateServerSetup> reactions;
	StateServerRunning(my_context ctx) : my_base( ctx )
	{
		Cli::writeDebugMsg("Enter StateServerRunning.");
		try
		{
			serverPtr = std::shared_ptr<server>(new server(context<StateServer>().port));
		}
		catch(...)
		{
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to start server on "+std::to_string(context<StateServer>().port));
			post_event(EvError());
		}

		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Server up and running.");
	}
	~StateServerRunning() { Cli::writeDebugMsg("Exit StateServerRunning."); }

private:
	std::shared_ptr<server> serverPtr;

};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATESERVERRUNNING_H_ */
