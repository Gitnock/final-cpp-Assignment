// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: April 13, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include <iostream>
#include <deque>
class Workstation: public Station
{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(const std::string&);
	Workstation(Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&) = delete;
	Workstation& operator=(Workstation&&) = delete;
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&);
	Workstation& operator+=(CustomerOrder&&);
};

#endif