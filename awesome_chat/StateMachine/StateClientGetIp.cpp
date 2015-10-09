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

sc::result StateClientGetIp::react( const EvUserInput & event)
{
	context<StateClient>().ip = event.userInput;
	return transit<StateClientGetPort>();
}

} /* namespace StateMachine */
