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
			sc::custom_reaction<EvClientDisconnect>,
			sc::custom_reaction<EvUserInput> >reactions;

	StateClientConnected(my_context ctx) : my_base( ctx )
	{
		Cli::writeDebugMsg("Enter StateClientConnected.");

		bool connectFailed = false;
		try
		{
			std::string& ip = context<StateClient>().ip;
			uint port = context<StateClient>().port;
			Simple_Socket socket;

			socket.connect(ip, port);

			m_client = std::shared_ptr<ClientInfo>(new ClientInfo(socket));
			disconnect = m_client->disconnected.connect(boost::bind(&StateClientConnected::OnDisconnect, this, _1));
			MsgRecived = m_client->recivedPacket.connect(boost::bind(&StateClientConnected::OnMsgRecivd, this, _1, _2));
		}
		catch(boost::system::error_code& e)
		{
			connectFailed = true;
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Got boost error_code: " + std::to_string(e.value()) + " : " + e.message() );
		}
		catch(std::exception& e)
		{
			connectFailed = true;
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, std::string("Got exception: ") + e.what() );
		}
		catch(...)
		{
			connectFailed = true;
		}

		if(connectFailed) {
			Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Unable to connect to server (ip: "+context<StateClient>().ip+" port: "+std::to_string(context<StateClient>().port)+" )");
			post_event(EvClientDisconnect());
		}
	}

	~StateClientConnected()
	{ Cli::writeDebugMsg("Exit StateClientConnected."); }

	sc::result react( const EvClientDisconnect & );
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
