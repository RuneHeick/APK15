/*
 * UserInput.cpp
 */

#include "UserInputHandler.h"

#include "cli.h"

UserInputHandler::UserInputHandler( std::function<void(std::shared_ptr<std::string>)> inputHandlerFunction ) {
	m_stopThread = false;
	m_inputHandlerFunc = inputHandlerFunction;
}

UserInputHandler::~UserInputHandler() {
	m_stopThread = true;
	if(m_thread.joinable())
		m_thread.join();
}

void UserInputHandler::Start() {
	m_stopThread = false;
	m_thread = std::thread(&UserInputHandler::HandleUserInput,this);
}

void UserInputHandler::HandleUserInput() {
	const std::chrono::milliseconds sleepTime_ms(10);
	while(!m_stopThread)	{
		std::shared_ptr<std::string> usrInput = std::make_shared<std::string>(Cli::getUserInput());
		if(m_inputHandlerFunc)
			m_inputHandlerFunc(usrInput);

		std::this_thread::sleep_for(sleepTime_ms);
	}
}
