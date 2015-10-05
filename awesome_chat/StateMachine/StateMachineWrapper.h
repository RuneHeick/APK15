/*
 * StateMachineWrapper.h
 */

#ifndef STATEMACHINE_STATEMACHINEWRAPPER_H_
#define STATEMACHINE_STATEMACHINEWRAPPER_H_

#include <mutex>

#include "ChatStateMachine.h"

namespace StateMachine {

class StateMachineWrapper {
public:
	StateMachineWrapper();

	void HandleUserInput(const std::shared_ptr<std::string>& str_ptr);
	void PostEvent(const sc::event_base & evt );
private:
	ChatStateMachine sm;
	std::mutex mtx;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATEMACHINEWRAPPER_H_ */
