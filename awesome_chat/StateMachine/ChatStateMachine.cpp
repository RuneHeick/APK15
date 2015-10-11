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
//		lock.unlock(); // Todo Henrik: Hvis nogen kalder postEvent inde fra state-maskinen vil det være nødvendigt at frigive låsen her. Se evt. eksemplet underneden. Kan ikke helt forstå vi ønsker at stå og tage den lås uden noget delay inden næste loop.
		PostVisitor vs;
		boost::apply_visitor( boost::bind(vs, _1, this) , val);
	//	lock.lock();
		q.pop();
	}

//	std::unique_lock<std::mutex> lock(m, std::defer_lock);
//	while(running)
//	{
//		lock.lock();
//		if(!q.empty())
//		{
//			SMEventVariant val = q.front();
//			lock.unlock();
//			PostVisitor vs;
//			boost::apply_visitor( boost::bind(vs, _1, this) , val);
//			lock.lock();
//			q.pop();
//		}
//		lock.unlock();
//		std::this_thread::sleep_for(std::chrono::milliseconds(10));
//	}
}


}

