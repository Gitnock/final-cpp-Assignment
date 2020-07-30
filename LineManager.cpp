// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: April 13, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include "LineManager.h"
#include "Utilities.h"
#include <fstream>

LineManager::LineManager(const std::string& src, std::vector<Workstation*>& workstations, std::vector<CustomerOrder>& custOrder) {
	Utilities util;
	std::string line, one, two;
	std::fstream file(src);
	size_t pos = 0;
	bool more = true;

	while (file) {
		while (getline(file, line, '\n')) {
			one = util.extractToken2(line, pos, more);
			for (size_t i = 0; i < workstations.size(); i++) {
				if (one == workstations[i]->getItemName()) {
					if (more) {
						two = util.extractToken2(line, pos, more);
						for (size_t j = 0; j < workstations.size(); j++) {
							if (two == workstations[j]->getItemName()) {
								workstations[i]->setNextStation(*workstations[j]);
							}
						}
					}
					AssemblyLineSorted.push_back(workstations[i]);
				}
			}
		}
	}
	m_cntCustomerOrder = custOrder.size();
	AssemblyLine = workstations;

	ToBeFilled = std::deque<CustomerOrder>(m_cntCustomerOrder);
	for (size_t i = 0; i < custOrder.size(); i++) {
		ToBeFilled[i] = std::move(custOrder[i]);
	}
}


bool LineManager::run(std::ostream& os)
{
	static size_t count = 0;
	os << "Line Manager Iteration: " << ++count << std::endl;
	if (!ToBeFilled.empty()) {
		*AssemblyLineSorted.at(0) += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
	for (auto&& i : AssemblyLine) {
		i->runProcess(os);
	}
	CustomerOrder tmp;
	for (auto&& j : AssemblyLine) {
		j->moveOrder();
		if (j->getIfCompleted(tmp)) {
			Completed.push_back(std::move(tmp));
		}
	}
	return Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const
{
	if (!Completed.empty()) {
		for (auto i = Completed.begin(); i != Completed.end(); i++)
		{
			(i)->display(os);
		}
	}
}

void LineManager::displayStations() const
{
	if (!AssemblyLine.empty()) {
		for (auto i : AssemblyLine)
			i->display(std::cout);
	}
}

void LineManager::displayStationsSorted() const
{
	for (auto&& i : AssemblyLineSorted) {
		i->display(std::cout);
	}
}
