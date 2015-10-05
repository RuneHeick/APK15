/*
 * StateHelperFunction.cpp
 */

#include "StateHelperFunctions.h"

#include <stdexcept>

#include "../cli.h"

namespace StateMachine {


int ParsePort(std::string& str) {
	int port;
	try {
		port = std::stoi(str);

		if(port <= 0 || port > 65535) {
			throw std::out_of_range("Out of range");
		}
	} catch(std::out_of_range& e) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Port out of range. Valid interval: [0,65535].");
		throw;
	} catch(std::invalid_argument& e) {
		Cli::writeLogMsg(Cli::LOGTYPE_ERROR, "Invalid input - unable to convert to an integer.");
		throw;
	}

	return port;
}

} /* namespace StateMachine */

