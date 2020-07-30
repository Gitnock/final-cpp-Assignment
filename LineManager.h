// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: April 13, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef SDDS_LINEMANGER_H
#define SDDS_LINEMANGER_H
#include <string>
#include "Workstation.h"
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include "CustomerOrder.h"
class LineManager
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	std::vector<Workstation*> AssemblyLineSorted;
	unsigned int m_cntCustomerOrder;

public:
	LineManager(const std::string&, std::vector<Workstation*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif