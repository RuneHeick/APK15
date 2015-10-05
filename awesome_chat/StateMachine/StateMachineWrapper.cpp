/*
 * StateMachineWrapper.cpp
 */

#include "StateMachineWrapper.h"
#include "StateSelectMode.h" // todo why??

namespace StateMachine {

StateMachineWrapper::StateMachineWrapper() {
	sm.initiate();
}

void StateMachineWrapper::HandleUserInput(std::shared_ptr<std::string> str_ptr) {
	std::lock_guard<std::mutex> lock(mtx);

	sm.usrInput = str_ptr;

	sm.process_event( EvUserInput() );
}

void StateMachineWrapper::PostEvent(const sc::event_base & evt ) {
	std::lock_guard<std::mutex> lock(mtx);
	sm.process_event(evt);
}

} /* namespace StateMachine */
