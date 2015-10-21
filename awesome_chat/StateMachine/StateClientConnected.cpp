/*
 * StateClientConnected.cpp
 */

#include "StateClientConnected.h"

#include "StateClientDisconnected.h"
#include "StateClientGetIp.h"

namespace StateMachine {

StateClientConnected::StateClientConnected(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter StateClientConnected.");

	bool connectFailed = false;
	try
	{
		std::string& ip = context<StateClient>().ip;
		uint port = context<StateClient>().port;
		Simple_Socket socket;

		socket.connect(ip, port);

		m_clientSocketPtr = std::shared_ptr<ClientInfo>(new ClientInfo(socket));
		disconnect = m_clientSocketPtr->disconnected.connect(boost::bind(&StateClientConnected::OnDisconnect, this, _1));
		MsgRecived = m_clientSocketPtr->recivedPacket.connect(boost::bind(&StateClientConnected::OnMsgRecivd, this, _1, _2));
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
	else
	{
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Connected to server");
	}
}

StateClientConnected::~StateClientConnected()
{
	Cli::writeDebugMsg("Exit StateClientConnected.");
}

sc::result StateClientConnected::react( const EvUserInput & userEvent ) {
	EventVariant event;
	try {
		event = context<StateClient>().inputParser.createEventFromInput("",userEvent.userInput);
	} catch(...) {
		Cli::writeLogMsg(Cli::LOGTYPE_WARNING, "Bad Input");
		return discard_event();
	}

	try {
		m_clientSocketPtr->Send(event);
	} catch(...) {
		return transit<StateClientDisconnected>();
	}

	return discard_event();
}

void StateClientConnected::OnDisconnect(ClientInfo const & client)
{
	disconnect.disconnect();
	MsgRecived.disconnect();
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Lost connection to server");
	context<ChatStateMachine>().postEvent(EvClientDisconnect());
}

void StateClientConnected::OnMsgRecivd(ClientInfo const & client, EventVariant msg)
{
	boost::apply_visitor(ClientMessageVisitor(), msg);
}


} /* namespace StateMachine */
