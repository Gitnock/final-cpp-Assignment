// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: Mar 31, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.
#include "Station.h"
#include "Utilities.h"
#include<iostream>
#include<iomanip>
#include <string> 
size_t Station::m_widthField = 0;
int Station::id_generator = 0;


//size_t mId;
//std::string mName;
//std::string mDesc;
//size_t mSerial;
//size_t mQuantity;

Station::Station(std::string line)
{
	Utilities util;
	char d = util.getDelimiter();
	size_t end = 0;
	bool ismore = false;

	mName = line.substr(0, line.find(d));
	end = line.find(d) + 1;

	mSerial = stoi(util.extractToken(line, end, ismore));
	end++;

	mQuantity = stoi(util.extractToken(line, end, ismore));
	end++;

	mDesc = util.extractToken(line, end, ismore);

	mId = ++id_generator;

	if (mName.length() > m_widthField) {
		m_widthField = mName.length();
		util.setFieldWidth(m_widthField);
	}
}
const std::string& Station::getItemName() const
{
	// TODO: insert return statement here
	return mName;
}
unsigned int Station::getNextSerialNumber()
{
	return mSerial++;
}
unsigned int Station::getQuantity() const
{
	return mQuantity;
}
void Station::updateQuantity()
{
	if (mQuantity >= 1) {
		mQuantity--;
	}
}
void Station::display(std::ostream& os, bool full) const
{

	if (full) {
		//os << m_widthField << std::endl;
		os << "[" << std::setfill('0') << std::right << std::setw(3) << mId << "]" << " Item: " << std::left << std::setfill(' ') << std::setw(m_widthField) << getItemName()
			<< " [" << std::setfill('0') << std::setw(6) << std::right << mSerial << "] " << "Quantity: " << std::left << std::setfill(' ') << std::setw(m_widthField) << getQuantity() << " Description: " << mDesc << std::endl;

	}
	else {

		os << "[" << std::setfill('0') << std::setw(3) << mId << "]" << " Item: " << std::left << std::setfill(' ') << std::setw(m_widthField) << mName
			<< " [" << std::setfill('0') << std::setw(6) << std::right << mSerial << "]" << std::endl;

	}


}
