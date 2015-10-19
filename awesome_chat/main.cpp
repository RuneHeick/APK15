#include <iostream>
#include <thread>
#include <stdio.h>
#include <signal.h>
#include <execinfo.h>
#include "Network/clientInfo.h"
#include "StateMachine/StateMachineWrapper.h"

void backTrace_sighandler(int sig) {
	const size_t MAX_TRACE_SIZE = 100;
	void *trace[MAX_TRACE_SIZE];
	char **messages = (char **)NULL;
	size_t trace_size = 0;

	// Get backtrace:
	trace_size = backtrace(trace, MAX_TRACE_SIZE);

	// print
	printf("Got signal %d\n", sig);
	messages = backtrace_symbols(trace, trace_size);

	/* skip first stack frame (points here) */
	printf("[bt] Execution path:\n");
	for(size_t i = 1;  i<trace_size; ++i)
	{
		printf("[bt] #%d %s\n", i, messages[i]);

		char syscom[256];
		sprintf(syscom,"addr2line %p -e awesome_chat", trace[i]); //last parameter is the name of this app
		system(syscom);
	}

	exit(0);
}

int main(){
	// Signal handler to catch segmentation faults:
	signal(SIGSEGV, backTrace_sighandler);

	// Create and initiate the state machine
	StateMachine::StateMachineWrapper statemachine;

	// Function pointer to handle input
	std::function<void(const std::string&)> inputHandlerFunc = std::bind(&StateMachine::StateMachineWrapper::HandleUserInput, &statemachine, std::placeholders::_1);

	// Start reading user intput
	while(true)	{
		std::string usrInput = Cli::getUserInput();

		if(inputHandlerFunc)
			inputHandlerFunc(usrInput);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

