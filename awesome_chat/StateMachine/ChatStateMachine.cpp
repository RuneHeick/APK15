/*
 * ChatStateMachine.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: stud
 */
#include "ChatStateMachine.h"
#include "boost/variant/static_visitor.hpp"
#include "boost/bind.hpp"

namespace StateMachine
{

ChatStateMachine::ChatStateMachine()
{
	m_thread = std::thread(std::bind(&ChatStateMachine::dequeue,this));
}


ChatStateMachine::~ChatStateMachine()
{
	{
		std::lock_guard<std::mutex> lock(m);
		running = false;
		c.notify_one();
	}
	m_thread.join();
}

void ChatStateMachine::dequeue(void)
{
	std::unique_lock<std::mutex> lock(m);
	while(running)
	{
		while(q.empty())
		{
		  c.wait(lock);
		}
		SMEventVariant val = q.front();
		PostVisitor vs;
		boost::apply_visitor( boost::bind(vs, _1, this) , val);
		q.pop();
	}
}


}

