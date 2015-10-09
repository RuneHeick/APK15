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

	void HandleUserInput(const std::string& str_ptr);
private:
	ChatStateMachine sm;
};

} /* namespace StateMachine */

#endif /* STATEMACHINE_STATEMACHINEWRAPPER_H_ */
