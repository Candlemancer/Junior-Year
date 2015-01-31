// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Implementation

#include <regex>
#include <vector>

#include "Shell.hpp"

// Default Constructor
Shell::Shell(void) {

	std::string currentLine;

	std::cout << "[cmd]: ";
	getCommand(currentLine);
	parseCommand(currentLine);
	runCommand(currentLine);

	// delete this;
	return;
}

// Read in a line of input from the user.
void Shell::getCommand(std::string& userInput) {

	std::getline(std::cin, userInput);

	return;
}

void Shell::parseCommand(std::string& commandString) {

	// std::regex word("(\\w+)(\\G\\s(\\S+)\\b)*");
	std::regex word("(\\S+)+");

	std::regex_iterator<std::string::iterator> currentMatch (
		commandString.begin(),
		commandString.end(),
		word);

	std::regex_iterator<std::string::iterator> endMatch;

	while (currentMatch != endMatch) {
		std::cout << "'" << currentMatch->str().c_str() << "'" << std::endl;
		currentMatch++;
	}

	return;
}


// Run the command specified in commandString with the remaining arguments
void Shell::runCommand(std::string& command) {

	auto PID = -1;
	std::vector<char *> commands;
	std::vector<char> first(command.begin(), command.end());
	commands.push_back(first.data());
	char** test = &commands[0];

	// Fork the Process
	PID = fork();

	// If parent (shell) wait for child
	if (PID == 0) {
		// NOTHING
	}
	// If child execute the command
	if (PID > 0) {
		std::cout << " > " << command.c_str() << std::endl;
		execvp(test[0], test);

	}
	// If error complain
	if (PID < 0) {
		std::cerr << "My Head A Splode!" << std::endl;
	}


	return;
}
