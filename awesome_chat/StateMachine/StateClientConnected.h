/*
 * StateClientConnected.h
 */

#ifndef STATEMACHINE_STATECLIENTCONNECTED_H_
#define STATEMACHINE_STATECLIENTCONNECTED_H_

#include "StateClient.h"
#include "../Network/clientInfo.h"
#include "../Events/Events.hpp"

namespace StateMachine {

struct StateClientConnected : sc::state<StateClientConnected, StateClient>
{
	typedef boost::mpl::list<
			sc::custom_reaction<EvClientDisconnect>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientConnected(my_context ctx) : my_base( ctx )
	{
		Cli::writeDebugMsg("Enter StateClientConnected.");
		try
		{
			std::string& ip = context<StateClient>().ip;
			uint port = context<StateClient>().port;
			Simple_Socket socket;

			socket.connect(ip, port);

			m_client = std::shared_ptr<ClientInfo>(new ClientInfo(socket));
			disconnect = m_client->disconnected.connect(boost::bind(&StateClientConnected::OnDisconnect, this, _1));
		}
		catch(...)
		{
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to connect to server (ip: "+context<StateClient>().ip+" port: "+std::to_string(context<StateClient>().port)+" )");
			post_event(EvClientDisconnect());
		}
	}

	~StateClientConnected()
	{ Cli::writeDebugMsg("Exit StateClientConnected."); }

	sc::result react( const EvClientDisconnect & );
	sc::result react( const EvUserInput & );
private:
	std::shared_ptr<ClientInfo> m_client;
	boost::signals2::scoped_connection disconnect;

	void OnDisconnect(ClientInfo& client)
	{
		post_event(EvClientDisconnect());
	}

};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTCONNECTED_H_ */
