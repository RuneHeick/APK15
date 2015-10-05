#ifndef _H_CONNECTEDRESSOURCE
#define _H_CONNECTEDRESSOURCE

#include <boost/bind.hpp>
#include "BaseRessource.h"
#include "../Network/clientInfo.h"
template<typename TList>
struct ConnectedStateRessource: public BaseRessource
{
	ConnectedStateRessource() = default;

	void Start(Simple_Socket& data)
	{

		if(m_client)
		{
			m_client->disconnected.disconnect(boost::bind(&ConnectedStateRessource::OnError, this, _1));
		}
		m_client = std::shared_ptr<ClientInfo<TList>>(new ClientInfo<TList>(data));
		m_client->disconnected.connect(boost::bind(&ConnectedStateRessource::OnError, this, _1));
	}

	void Stop()
	{
		if(m_client)
		{
			m_client->disconnected.disconnect(boost::bind(&ConnectedStateRessource::OnError, this, _1));
			m_client->Disconnect();
		}
	}

	std::shared_ptr<ClientInfo<TList>> m_client;

private:

	void OnError(ClientInfo<TList>& client){
		Error();
	}

};

#endif
