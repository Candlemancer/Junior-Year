# Jonathan Petersen
# A01236750
# RedirectionShell Assignment
# Makefile

CC=g++
CFLAGS=-c -std=c++11 -Wall -Wextra -Wpedantic
LDFLAGS=
SOURCES=Main.cpp Shell.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=RedirectionShell

all: prepare $(SOURCES) $(EXECUTABLE) cleanup

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

prepare:
	rm -rf $(OBJECTS) $(EXECUTABLE)

cleanup:
	rm -rf $(OBJECTS)
