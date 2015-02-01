NAME
	Shell

USAGE
	1. make -f makefile
	2. ./Shell

DESCRIPTION
	Creates a basic user interface shell. Commands are as follows:

		ptime - returns the amount of time spent waiting for child processes.
		history - prints a list of commands used in the order they were used.
		^ [number] - executes the command of index [number] from the history.

	Any other command is passed to the host shell for execution.


Compiled with GNU G++ 4.9.2 on OS X 10.9
Compatible with any POSIX-compliant system

Created by Jonathan Petersen
	Studying at Utah State University


