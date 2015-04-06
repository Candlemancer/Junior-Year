// Jonathan Petersen
// A01236750
// Scheduling Framework Assignment
// Page Table Interface

#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include "Event.hpp"

class PageTable {
public:

	bool virtual fetch(Event item) = 0;
	void virtual push(Event item) = 0;

};

#endif

