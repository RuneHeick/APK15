/*
 * StateClientGetIp.cpp
 */

#include "StateClientGetIp.h"

#include "StateClientGetPort.h"

namespace StateMachine {

StateClientGetIp::StateClientGetIp(my_context ctx) : my_base( ctx )
{
	Cli::writeDebugMsg("Enter StateClientGetIp.");
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, "Set the server ip:");
}

sc::result StateClientGetIp::react( const EvUserInput & )
{
	context<StateClient>().chatClient.SetServerIp(*context<ChatStateMachine>().usrInput);
	return transit<StateClientGetPort>();
}

} /* namespace StateMachine */
