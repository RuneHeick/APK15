#ifndef _H_BASERESSOURCE
#define _H_BASERESSOURCE

#include "../NetSocket.h"
#include <boost/signals2.hpp>

class BaseRessource
{
	virtual void Start(Simple_Socket& data) = 0;

	virtual void Stop() = 0;

	boost::signals2::signal<void ()> Error;
};


#endif

