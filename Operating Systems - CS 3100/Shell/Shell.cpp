// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Implementation

#include <regex>

#include "Shell.hpp"

// Default Constructor
Shell::Shell(void) {

	std::string currentLine;

	std::cout << "[cmd]: ";
	getCommand(currentLine);
	// parseCommand(currentLine);
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

	std::regex word("(\\w+)( \\w+)*");
	std::smatch results;

	auto didMatch = std::regex_search(commandString, results, word);

	if (didMatch) {
		for (auto&& i : results) {
			std::cout << i << std::endl;
		}
	}
	else {
		std::cerr << "Could not verify command!" << std::endl;
	}


}


// Run the command specified in commandString with the remaining arguments
void Shell::runCommand(std::string& command) {

	auto PID = -1;
	command = "ls";
	char* args[1];

	// Fork the Process
	PID = fork();

	// If parent (shell) wait for child
	if (PID == 0) {
		// NOTHING
	}
	// If child execute the command
	if (PID > 0) {
		std::cout << " > " << command << std::endl;
		execvp(command.c_str(), args);

	}
	// If error complain
	if (PID < 0) {
		std::cerr << "My Head A Splode!" << std::endl;
	}


	return;
}
