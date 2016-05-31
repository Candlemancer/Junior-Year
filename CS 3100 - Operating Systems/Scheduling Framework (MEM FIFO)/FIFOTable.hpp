// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// FIFO Page Table Header

#ifndef FIFO_TABLE_HPP
#define FIFO_TABLE_HPP

#include "PageTable.hpp"

#include <deque>

#include "Event.hpp"

class FIFOTable : public PageTable {
public:
	FIFOTable(unsigned int numPages = 10);

	bool fetch(Event item);
	void push(Event item);
	
private:
	std::deque<Event> pgTable;
	unsigned int m_numPages;

};

#endif
