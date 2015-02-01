// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Implementation

#include <algorithm>
#include <regex>

#include "Shell.hpp"

// Default Constructor
Shell::Shell(void) {

	std::vector<const char *> commands;

	std::cout << "[cmd]: ";
	getCommand(commands);
	runCommand(commands);

	// delete this;
	return;
}

// Read in a line of input from the user.
void Shell::getCommand(std::vector<const char *>& output) {

	// Setup the Regular Expression and find matches
	std::vector<std::string> strings;
	std::regex word("(\\S+)+");
	std::string commandString;

	std::getline(std::cin, commandString);

	std::regex_iterator<std::string::iterator> currentMatch (
		commandString.begin(),
		commandString.end(),
		word);

	std::regex_iterator<std::string::iterator> endMatch;

	// Add the matches to a vector of strings
	std::transform(
		currentMatch,
		endMatch,
		back_inserter(strings),
		[](std::regex_iterator<std::string::iterator>::value_type token) { return token.str(); }
	);

	for (auto&& i : strings) {
		output.push_back(i.c_str());
	}

	output.push_back('\0');
	return;
}


// Run the command specified in commandString with the remaining arguments
void Shell::runCommand(std::vector<const char *>& command) {

	auto PID = -1;
	char* const* test = const_cast<char* const*>(command.data());

	// Fork the Process
	PID = fork();

	// If parent (shell) wait for child
	if (PID == 0) {
		// NOTHING
	}
	// If child execute the command
	if (PID > 0) {
		// std::cout << " > '" << test[0] << "'" << std::endl;
		execvp(test[0], test);

	}
	// If error complain
	if (PID < 0) {
		std::cerr << "My Head A Splode!" << std::endl;
	}


	return;
}
