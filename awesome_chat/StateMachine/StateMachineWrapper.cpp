/*
 * StateMachineWrapper.cpp
 */

#include "StateMachineWrapper.h"
#include "StateSelectMode.h"

namespace StateMachine {

StateMachineWrapper::StateMachineWrapper() {
	sm.initiate();
}

void StateMachineWrapper::HandleUserInput(const std::string& str_ptr) {
	sm.postEvent<EvUserInput>( EvUserInput(str_ptr) );
}


} /* namespace StateMachine */
