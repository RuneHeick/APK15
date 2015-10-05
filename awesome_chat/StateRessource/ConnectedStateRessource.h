#ifndef _H_CONNECTEDRESSOURCE
#define _H_CONNECTEDRESSOURCE

#include "BaseRessource.h"
#include "../clientInfo.h"

template<typename TList>
class ConnectedStateRessource: public BaseRessource
{
	void Start(Simple_Socket& data)
	{
		client = ClientInfo<TList>(data);
	}

	void Stop()
	{

	}
private:
	ClientInfo<TList> client;

};

#endif
