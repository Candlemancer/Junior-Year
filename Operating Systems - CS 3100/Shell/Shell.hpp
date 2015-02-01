// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Header

#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <vector>
#include <string>
#include <chrono>

#include <unistd.h>
#include <term.h>

class Shell {

public:
	Shell(void);

private:
	void getCommand();
	void runCommand();

	char * const * parseCommand();
	void runHistory();

	void printWaitTime();
	void printHistory();

	std::vector<std::string> command;
	std::vector<std::vector<std::string>> history;

	std::string exitCommand = "exit";
	std::string timeCommand = "ptime";
	std::string histCommand = "history";
	std::string backCommand = "^";
	std::chrono::duration<double> waitTime;

};

#endif
