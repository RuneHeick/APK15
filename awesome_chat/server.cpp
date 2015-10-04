
#include "server.h"

#include "cli.h"

server::server() {
	// TODO Auto-generated constructor stub
}

server::~server() {
	// TODO Auto-generated destructor stub
}

void server::SetPort(uint16_t port) {
	// todo implement.
	Cli::writeLogMsg(Cli::LOGTYPE_INFO, std::string("Port set to: ") + std::to_string(port) );
}
