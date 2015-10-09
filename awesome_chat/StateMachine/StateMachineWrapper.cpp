/*
 * StateMachineWrapper.cpp
 */

#include "StateMachineWrapper.h"
#include "StateSelectMode.h" // todo why??

namespace StateMachine {

StateMachineWrapper::StateMachineWrapper() {
	sm.initiate();
}

void StateMachineWrapper::HandleUserInput(const std::shared_ptr<std::string>& str_ptr) {
	std::lock_guard<std::mutex> lock(mtx);

	sm.postEvent<EvUserInput>( EvUserInput(*str_ptr) );
}


} /* namespace StateMachine */
