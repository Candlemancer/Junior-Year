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

		checkPipes();
		pipeOutput.erase(pipeOutput.begin(), pipeOutput.end());
		for (auto&& i : compoundCommand) {

			command = i;
			compoundCommand.erase(compoundCommand.begin());
			runCommand();
			if (command[0] != "") { history.push_back(command); }
			command.erase(command.begin(), command.end());

		}

		compoundCommand.erase(compoundCommand.begin(), compoundCommand.end());
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
	int toParent[2];
	int toChild[2];

	if ( pipe(toParent) ) { std::cout << "Could not open a pipe" << std::endl; }
	if ( pipe(toChild) ) { std::cout << "Could not open a pipe" << std::endl; }

	if (command[0] == exitCommand) { exit(0); }
	if (command[0] == backCommand) { runHistory(); }
	if (command[0] == "") { return; }

	PID = fork();

	// If error complain
	if (PID < 0) { std::cerr << "Unable to spawn child process!" << std::endl; exit(-1); }

	// If parent (shell) wait for child
	if (PID > 0) {

		// char readbuf[999999];
		// int numRead = 0;

		// Close the pipes we don't use
		close(toParent[PIPE_WRITE]);
		close(toChild[PIPE_READ]);

		if (pipeOutput.size() > 0) { write(toChild[PIPE_WRITE], &pipeOutput[0], pipeOutput.size()); }

		close(toChild[PIPE_WRITE]);
		pipeOutput.erase(pipeOutput.begin(), pipeOutput.end());
		// std::cout << "String Size: " << pipeOutput.size() << std::endl;

		// Time how long it takes to wait for the child process
		using std::chrono::system_clock;

		system_clock::time_point start = system_clock::now();
		waitpid(PID, nullptr, 0);
		system_clock::time_point stop = system_clock::now();

		waitTime += (stop - start);

		// Read Child's STDOUT into pipeOutput
		pipeOutput.resize(999999);
		// numRead =
		read(toParent[PIPE_READ], &pipeOutput[0], 999999);
		// std::cout << "Bytes Read: " << numRead << std::endl;
		// std::cout << "First character: " << pipeOutput[0] << std::endl;
		// std::cout << "String Size: " << pipeOutput.size() << std::endl;
		// pipeOutput.append('\0');
		// pipeOutput[numRead] = '\0';

		close(toParent[PIPE_READ]);
		std::cout << " > '" << pipeOutput << "'" << std::endl;

		return;
	}

	// If child execute the command
	if (PID == 0) {
		// Close the pipes we don't use
		close(toParent[PIPE_READ]);
		close(toChild[PIPE_WRITE]);

		// std::cout << compoundCommand.size() << std::endl;
		if (compoundCommand.size() > 0) {

			std::cout << "Duping Child STDOUT to Parent." << std::endl;
			dup2(toParent[PIPE_WRITE], STDOUT);

		}
		if (pipeOutput.size() > 0) {
			std::cout << "Duping Child STDIN to Parent." << std::endl;
			dup2(toChild[PIPE_READ], STDIN);
		}

		close(toParent[PIPE_WRITE]);
		close(toChild[PIPE_READ]);

		// Run our internal commands
		checkRedirect();
		if (command[0] == timeCommand) { printWaitTime(); exit(0); }
		if (command[0] == histCommand) { printHistory(); exit(0); }
		// if (args[0] == backCommand) { runHistory(); /*exit(0);*/ }

		// Pass everything else off to the OS
		auto args = parseCommand();
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
// Replace the ^ commands in the history with the actual command run
// This prevents infinite loops by calling ^ on ^ commands.
void Shell::runHistory() {

	auto index = 0u;

	try { index = stoi(command[1]); }
	catch (std::exception e) { index = 0; }

	if (index > history.size() || index == 0) { command[0] = ""; return; }

	command = history[index];
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

void Shell::checkRedirect() {

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
					// std::cout << "Could not open file" << std::endl;
				}

				command.erase(command.begin() + i);
				// Reset the search in case another token is in a lower index.
				i = 0;
				continue;
			}

			if(command[i] == "<") {
				// std::cout << "I found a <!" << std::endl;

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
				// Reset the search in case another token is in a lower index.
				i = 0;
				continue;
			}

		}

	return;
}

void Shell::checkPipes() {

	for (unsigned int i = 0; i < command.size(); i++) {

		if (command[i] == "|") {
			// std::cout << "Found | at " << i << std::endl;
			std::vector<std::string> temp = command;
			temp.erase(temp.begin() + i, temp.end());
			compoundCommand.push_back(temp);
			command.erase(command.begin(), command.begin() + i + 1);
			i = 0;
		}

	}

	if (compoundCommand.size() > 0) {
		compoundCommand.push_back(command);
		command.erase(command.begin(), command.end());
		command.push_back("");
	}
	else {
		compoundCommand.push_back(command);
	}

	return;
}
