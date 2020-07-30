// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: April 13, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#include "Workstation.h"

Workstation::Workstation(const std::string& line):Station(line)
{
	m_pNextStation = nullptr;
}

void Workstation::runProcess(std::ostream& os)
{
	if (!m_orders.empty() && !m_orders.front().isOrderFilled())
	{

		m_orders.front().fillItem(*this, os);
	}


}

bool Workstation::moveOrder()
{
	bool out = false;

	if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName()) && m_pNextStation) {
		*m_pNextStation += std::move(m_orders.front());
		m_orders.pop_front();
		out = true;
	}
	return out;
}

void Workstation::setNextStation(Station& station)
{
	m_pNextStation = (Workstation*)&station;
}

const Workstation* Workstation::getNextStation() const
{
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order)
{
	bool isDone = false;
	if (!m_orders.empty() && m_orders.front().isOrderFilled())
	{
		order = std::move(m_orders.front());
		m_orders.pop_front();
		return true;
	}
	return isDone;
}

void Workstation::display(std::ostream& os)
{
	os << this->getItemName() << " --> ";
	if (m_pNextStation)
		os << m_pNextStation->getItemName();
	else {
		os <<"END OF LINE";
	}
	os << std::endl;

}

Workstation& Workstation::operator+=(CustomerOrder&& order)
{
	// TODO: insert return statement here
	m_orders.push_back(std::move(order));
	return *this;
}
