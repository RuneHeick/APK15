/*
 * UserInputHandler.h
 */

#ifndef USERINPUTHANDLER_H_
#define USERINPUTHANDLER_H_

#include <memory>
#include <thread>
#include <functional>

class UserInputHandler {
public:
	UserInputHandler( std::function<void(std::shared_ptr<std::string>)> inputHandlerFunction );
	~UserInputHandler();
	void Start();

private:
	void HandleUserInput(); // Thread function

	std::function<void(std::shared_ptr<std::string>)> m_inputHandlerFunc; // Function pointer to handle input
	bool m_stopThread;
	std::thread m_thread; // The thread
};

#endif /* USERINPUTHANDLER_H_ */
