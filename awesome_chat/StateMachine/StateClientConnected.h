/*
 * StateClientConnected.h
 */

#ifndef STATEMACHINE_STATECLIENTCONNECTED_H_
#define STATEMACHINE_STATECLIENTCONNECTED_H_

#include "StateClient.h"
#include "../Network/clientInfo.h"
#include "../event.h"
#include "../StateRessource/RessourceManager.h"

namespace StateMachine {

struct StateClientConnected : sc::simple_state<StateClientConnected, StateClient>
{
	typedef boost::mpl::list<
			sc::custom_reaction<EvClientDisconnect>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientConnected()
	{
		Cli::writeDebugMsg("Enter StateClientConnected.");
		try
		{
			RessourceManager::ConnectedStateRec->Start(context<StateClient>().chatClient);
			errorConnection = RessourceManager::ConnectedStateRec->Error.connect(boost::bind(&StateClientConnected::OnError, this)); // will disconnect on destruction;
		}
		catch(...)
		{
			post_event(EvClientDisconnect());
		}
	}

	~StateClientConnected() { Cli::writeDebugMsg("Exit StateClientConnected."); }

	void OnError()
	{
		post_event(EvClientDisconnect());
	}

	sc::result react( const EvClientDisconnect & );
	sc::result react( const EvUserInput & );
private:
	boost::signals2::scoped_connection errorConnection;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTCONNECTED_H_ */
