# Jonathan Petersen
# A01236750
# Shell Assignment
# Makefile

CC=g++-4.9
CFLAGS=-c -std=c++11 -Wall -Wextra -Wpedantic
LDFLAGS=
SOURCES=Main.cpp Shell.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Shell

all: prepare $(SOURCES) $(EXECUTABLE) cleanup

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

prepare:
	rm -rf $(OBJECTS) $(EXECUTABLE)

cleanup:
	rm -rf $(OBJECTS)
