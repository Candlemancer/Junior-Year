// Jonathan Petersen
// A01236750
// Scheduilng Framework Assignment
// FIFO Page Table Implementation

#include "FIFOTable.hpp"

FIFOTable::FIFOTable(unsigned int numPages) : 
	m_numPages(numPages) {}


bool FIFOTable::fetch(Event item) {

	// Walk the page table
	for (auto&& i : pgTable) {
		// Check if the Page is already loaded
		if (i == item) { return true; }
	}

	// Otherwise add the item to the page table
	push(item);

	// And return a page fault to restart the process
	return false;
}

void FIFOTable::push(Event item) {

	// Kill the first element if table is full
	while (pgTable.size() > m_numPages) { pgTable.pop_front(); }

	// Add the new element
	pgTable.push_back(item);
	
	return;
}
