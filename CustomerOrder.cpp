#include "CustomerOrder.h"
#include "Utilities.h"
#include <vector>
#include <iomanip>
#include <algorithm>
size_t CustomerOrder::m_widthField=0;

CustomerOrder::CustomerOrder(std::string& line)
{
	Utilities util;
	char d = util.getDelimiter();
	size_t end = 0;
	bool ismore = false;


	m_name = line.substr(0, line.find(d));
	end = line.find(d) + 1;

	m_product = util.extractToken2(line, end, ismore);


	m_cntItem = std::count(line.begin(), line.end(), util.getDelimiter()) - 1;



	this->m_lstItem = new Item * [m_cntItem];

	for (size_t i = 0; i < m_cntItem; i++) {

		m_lstItem[i] = new Item(util.extractToken2(line, end, ismore));
	}


	if (util.getFieldWidth() > m_widthField)
	{
		m_widthField = util.getFieldWidth();
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder&)
{
	throw std::string("Cannot make copies.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& that) noexcept
{
	*this = std::move(that);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& that) noexcept
{
	// TODO: insert return statement 
	if (this != &that) {
		m_lstItem = that.m_lstItem;
		m_name = that.m_name;
		m_product = that.m_product;
		m_cntItem = that.m_cntItem;
		that.m_lstItem = nullptr;
		that.m_name = "";
		that.m_cntItem = 0u;
		that.m_product = "";
	}
	return *this;
}

CustomerOrder::~CustomerOrder()
{
	delete[] m_lstItem;
	m_lstItem = nullptr;
}

bool CustomerOrder::isOrderFilled() const
{
	bool isGood = true;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_isFilled == false)
			isGood = false;
	}
	return isGood;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const
{
	bool isGood = true;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_itemName == itemName)
		{
			if (m_lstItem[i]->m_isFilled == false)
				isGood = false;
		}
	}
	return isGood;

}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (station.getItemName() == m_lstItem[i]->m_itemName)
		{
			if (station.getQuantity() > 0)
			{
				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				os << "    Filled " << m_name << ", "
					<< m_product << " [" << station.getItemName() << "]" << std::endl;
			}
			else
			{
				os << "    Unable to fill " << m_name << ", "
					<< m_product << " [" << station.getItemName() << "]" << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++)
	{
		os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
		os << std::setw(16) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_isFilled) os << "FILLED";
		else os << "MISSING";

		os << std::endl;
	}
	
}
