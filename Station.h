// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: Mar 31, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

class Station
{
	size_t mId;
	std::string mName;
	std::string mDesc;
	size_t mSerial;
	size_t mQuantity;
	static size_t m_widthField;
	static int id_generator;
public:
	Station(std::string line);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif