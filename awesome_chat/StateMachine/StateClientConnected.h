/*
 * StateClientConnected.h
 */

#ifndef STATEMACHINE_STATECLIENTCONNECTED_H_
#define STATEMACHINE_STATECLIENTCONNECTED_H_

#include "StateClient.h"
#include "../Network/clientInfo.h"
#include "../Events/Events.hpp"

namespace StateMachine {


struct ClientMessageVisitor : boost::static_visitor<void>
{

	void operator()(EventMsg& event) const
	{
		Cli::writeChatMsg(event.getSender(), event.getMessage());
	}

	// Do nothing for all other messages
	template<typename T>
	void operator()(T& event) const
	{
	}

};

struct StateClientConnected : sc::state<StateClientConnected, StateClient>
{
	typedef boost::mpl::list<
			sc::transition<EvClientDisconnect, StateClientDisconnected>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientConnected(my_context ctx);
	~StateClientConnected();

	sc::result react( const EvUserInput & );
private:
	boost::signals2::scoped_connection disconnect;
	boost::signals2::scoped_connection MsgRecived;
	std::shared_ptr<ClientInfo> m_client;

	void OnDisconnect(ClientInfo const & client)
	{
		context<ChatStateMachine>().postEvent(EvClientDisconnect());
	}

	void OnMsgRecivd(ClientInfo const & client, EventVariant msg)
	{
		boost::apply_visitor(ClientMessageVisitor(), msg);
	}

};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATECLIENTCONNECTED_H_ */
