/*
 * BoostStateMachine.h
 */

#ifndef STATEMACHINE_CHATSTATEMACHINE_H_
#define STATEMACHINE_CHATSTATEMACHINE_H_

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

#include "../cli.h"

namespace StateMachine {

namespace sc = boost::statechart;

struct EvServerMode : sc::event<EvServerMode> {};
struct EvClientMode : sc::event<EvClientMode> {};
struct EvError : sc::event<EvError> {};
struct EvSetupDone : sc::event<EvSetupDone> {};
struct EvClientConnect : sc::event<EvClientConnect> {};
struct EvClientDisconnect : sc::event<EvClientDisconnect> {};
struct EvClientIpDone : sc::event<EvClientIpDone> {};
struct EvUserInput : sc::event<EvUserInput> {
	EvUserInput(std::string uI): userInput(uI)
	{}
	std::string userInput;
};

// States forward declarations
struct StateSelectMode;
struct StateServer;
struct StateClient;
struct StateServerSetup;
struct StateClientDisconnected;
struct StateClientGetIp;
struct PostVisitor;

// Varinat

typedef boost::variant<EvServerMode,EvClientMode,EvError,EvSetupDone,EvClientConnect,EvClientDisconnect,EvClientIpDone,EvUserInput> SMEventVariant;




struct ChatStateMachine  : public sc::state_machine<ChatStateMachine, StateSelectMode>
{
	friend class PostVisitor;
	ChatStateMachine();

	~ChatStateMachine();

	template<typename T>
	void postEvent(const T& event)
	{
		std::lock_guard<std::mutex> lock(m);
		SMEventVariant var = event;
		q.push(var);
		c.notify_one();
	}

private:
	void dequeue(void);

	std::thread m_thread;
	std::queue<SMEventVariant> q;
	std::mutex m;
	std::condition_variable c;
	bool running;

};

struct PostVisitor : boost::static_visitor< >
{
	template<typename T>
	void operator()(T& event,ChatStateMachine*  sm ) const
	{
		sm->process_event(event);
	}
};



} /* namespace StateMachine */

#endif /* STATEMACHINE_CHATSTATEMACHINE_H_ */
