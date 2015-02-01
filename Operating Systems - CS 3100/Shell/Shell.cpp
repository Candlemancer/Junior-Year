// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Implementation

#include <algorithm>
#include <regex>
#include <sys/wait.h>

#include "Shell.hpp"

// Default Constructor
Shell::Shell(void) :
	waitTime() {

	// std::vector<std::vector<char const *> history;
	// char const * exitCommand = "exit";

	while (true) {
		std::cout << "[cmd]: ";

		getCommand();
		runCommand();

		history.push_back(command);
		command.erase(command.begin(), command.end());
	}

	// delete this;
	return;
}

// Read in a line of input from the user.
void Shell::getCommand() {

	// std::vector<std::string> strings;
	std::string commandString;
	std::regex word("(\\S+)+");

	// Read in a line of user input
	std::getline(std::cin, commandString);

	// Setup the Regular Expression and find matches
	std::regex_iterator<std::string::iterator> currentMatch (
		commandString.begin(),
		commandString.end(),
		word);

	std::regex_iterator<std::string::iterator> endMatch;

	// Add the matches to a vector of strings
	std::transform(
		currentMatch,
		endMatch,
		back_inserter(command),
		[](std::regex_iterator<std::string::iterator>::value_type token) { return token.str(); }
	);

	// for (auto&& i : strings) { output.push_back(i.c_str()); }

	// execvp expects a null-terminated list of null-terminated strings
	// command.push_back("\0");

	return;
}


// Run the command specified in commandString with the remaining arguments
void Shell::runCommand() {

	auto PID = -1;

	// Convert string to c_string
	std::vector<char const *> test;
	for (auto&& i : command) {
		test.push_back(i.c_str());
	}
	test.push_back('\0');
	char * const * args = const_cast<char* const*>(test.data());

	// std::cout << " > '" << args[0] << "'" << std::endl;

	// Check for exit condition
	if (args[0] == exitCommand) { exit(0); }
	// std::cout << args[0] << std::endl;


	// Fork the Process
	PID = fork();

	// If error complain
	if (PID < 0) { std::cerr << "My Head A Splode!" << std::endl; exit(-1); }

	// If parent (shell) wait for child, and time the wait
	if (PID > 0) {
		using std::chrono::system_clock;

		system_clock::time_point start = system_clock::now();
		waitpid(PID, nullptr, 0);
		system_clock::time_point stop = system_clock::now();

		waitTime += (stop - start);
	}

	// If child execute the command
	if (PID == 0) {

		// Run our internal commands
		if (args[0] == timeCommand) { std::cout << waitTime.count() << std::endl; exit(0); }
		if (args[0] == histCommand) {
			for (auto&& i: history) {
				for (auto&& j : i) {
					std::cout << j << " ";
				}
				std::cout << std::endl;
			}
			exit(0);
		}
		if (args[0] == backCommand) {

			int index = atoi(args[1]) - 1;

		 	// Convert string to c_string
			std::vector<char const *> test;
			for (auto&& i : history[index]) {
				test.push_back(i.c_str());
			}
			test.push_back('\0');
			char * const * args = const_cast<char* const*>(test.data());

			execvp(args[0], args);
			exit(0);
		}


		// Pass everything else off to the OS
		execvp(args[0], args);
		exit(0);
	}


	return;
}

// void Shell::execute(char * const * command) {




// }
