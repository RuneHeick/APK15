
#include "client.h"

#include "cli.h"

client::client() {
	connected = false;
	m_ServerPort = 0;
}

void client::SetServerIp(std::string const & ip)
{
	m_ServerIp = ip;
}

void client::SetPort(uint16_t port)
{
	m_ServerPort = port;
}

bool client::Connect() {
	try{
//		networkSocket.Connect(m_ServerIp, m_ServerPort); // todo add this line.
		Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Connected to: ") + m_ServerIp + std::string(" Port: ") + std::to_string(m_ServerPort));
		connected = true;
	} catch (boost::system::error_code& error) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR,
				std::string("Failed to connect: ") + m_ServerIp
				+ std::string(" Port: ") + std::to_string(m_ServerPort)
				+ std::string(" Error: ") + error.message());
	}

	return connected;
}

void client::Disconnect() {
	connected = false;
}

void client::ParseUserInput(std::string const & usrInput) {
	usrInputParser.createEventFromInput(usrInput);
}
