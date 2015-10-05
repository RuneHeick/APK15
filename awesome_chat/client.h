
#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdint>
#include <string>

#include "messageParser.h"
#include "NetSocket.h"

class client {
public:
	client();

	void SetServerIp(std::string const & ip);
	void SetPort(uint16_t port);
	bool Connect();
	void Disconnect();

	void ParseUserInput(std::string const & usrInput);
private:
	MessageParser usrInputParser;
	// todo SimpleSocket networkSocket();

	std::string m_ServerIp;
	uint16_t m_ServerPort;

	bool connected;
};

#endif /* CLIENT_H_ */
