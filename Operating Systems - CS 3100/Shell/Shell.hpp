// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Header

#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <iostream>
#include <string>

#include <unistd.h>
#include <term.h>

class Shell {

public:
	Shell(void);

private:
	void getCommand(std::string& userInput);
	void parseCommand(std::string& commandString);
	void runCommand(std::string& command);


};

#endif
