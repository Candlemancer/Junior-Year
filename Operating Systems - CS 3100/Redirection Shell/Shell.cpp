// Jonathan Petersen
// A01236750
// Shell Assignment
// Shell Class Implementation

#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <sys/wait.h>
#include <fcntl.h>

#include "Shell.hpp"

// Default Constructor
Shell::Shell(void) :
	waitTime() {

	while (true) {
		std::cout << "[cmd]: ";

		getCommand();
		runCommand();

		history.push_back(command);
		command.erase(command.begin(), command.end());
	}

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

	return;
}


// Run the command specified in commandString with the remaining arguments
void Shell::runCommand() {

	auto PID = -1;
	auto args = parseCommand();

	if (args[0] == exitCommand) { exit(0); }
	PID = fork();

	// If error complain
	if (PID < 0) { std::cerr << "Unable to spawn child process!" << std::endl; exit(-1); }

	// If parent (shell) wait for child
	if (PID > 0) {
		// Time how long it takes to wait for the child process
		using std::chrono::system_clock;

		system_clock::time_point start = system_clock::now();
		waitpid(PID, nullptr, 0);
		system_clock::time_point stop = system_clock::now();

		waitTime += (stop - start);

		// Replace the ^ commands in the history with the actual command run
		// This prevents infinite loops by calling ^ on ^ commands.
		if (args[0] == backCommand) {
			auto index = atoi(command[1].c_str()) - 1;
			command = history[index];
		}
	}

	// If child execute the command
	if (PID == 0) {

		// Run our internal commands
		if (args[0] == timeCommand) { printWaitTime(); exit(0); }
		if (args[0] == histCommand) { printHistory(); exit(0); }
		if (args[0] == backCommand) { runHistory(); exit(0); }
		for (unsigned int i = 0; i < command.size(); i++) {
			if (command[i] == ">") {
				// std::cout << "I found a >!" << std::endl;

				auto fd_out = open(
					command[i + 1].c_str(),
					O_WRONLY |
					O_CREAT |
					O_TRUNC,
					// 0666, though by default my process can only grant 0644
					(S_IRWXU ^ S_IXUSR) |
					(S_IRWXG ^ S_IXGRP) |
					S_IROTH
				);

				if (fd_out > 0) {
					// std::cout << "And opened a file!" << std::endl;
					command.erase(command.begin() + i + 1);
					dup2(fd_out, STDOUT);
					close(fd_out);
				}
				else {
					std::cout << "Could not open file" << std::endl;
				}

				command.erase(command.begin() + i);
			}
			if(command[i] == "<") {

				auto fd_in = open(command[i + 1].c_str(), O_RDONLY);

				if (fd_in > 0) {
					command.erase(command.begin() + i + 1);
					dup2(fd_in, STDIN);
					close(fd_in);
				}
				else {
					std::cout << "Could not read from file" << std::endl;
				}

				command.erase(command.begin() + i);
			}
		}

		// Pass everything else off to the OS
		args = parseCommand();
		execvp(args[0], args);
		exit(0);
	}

	return;
}

// Transform the command into the proper form for execvp.
char * const * Shell::parseCommand() {

	std::vector<char const *> commandChars;

	for (auto&& i : command) {
		commandChars.push_back(i.c_str());
	}
	// execvp requires a null-terminated list of arguments
	commandChars.push_back('\0');

	return const_cast<char* const*>(commandChars.data());
}

// Run a specific command in the history.
void Shell::runHistory() {

	auto index = atoi(command[1].c_str()) - 1;
	command = history[index];

	auto args = parseCommand();
	execvp(args[0], args);

	return;
}

// Pretty print the waitTime variable.
void Shell::printWaitTime() {

	using std::chrono::duration_cast;

	auto seconds = duration_cast<std::chrono::seconds> (waitTime);
	auto milliseconds = duration_cast<std::chrono::milliseconds> (waitTime - seconds);
	auto microseconds = duration_cast<std::chrono::microseconds> (waitTime - seconds - milliseconds);

	std::cout << "Time spent executing child processes: "
		<< seconds.count() << " seconds "
		<< milliseconds.count() << " milliseconds "
		<< microseconds.count() << " microseconds "
		<< std::endl;

	return;
}

// Show all commands in the history, including the history command.
void Shell::printHistory() {

	for (auto&& i: history) {

		for (auto&& j : i) {
			std::cout << j << " ";
		}

		std::cout << std::endl;
	}
	// Fake entry to cover the command calling this function.
	std::cout << "history" << std::endl;

	return;
}
