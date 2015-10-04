
#include "client.h"

#include "cli.h"

client::client() {
	// TODO Auto-generated constructor stub
}

client::~client() {
	// TODO Auto-generated destructor stub
}

void client::Connect(std::string ip, uint16_t port) {
	// todo implement.
	Cli::writeDebugMsg(std::string("Ip set to: ") + ip + std::string(" and port set to: ") + std::to_string(port) );
}
