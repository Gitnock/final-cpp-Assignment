// Name:               Enock lubega
// Seneca Student ID:  ID:154192181
// Seneca email:       elubega@myseneca.ca
// Date of completion: Mar 31, 2020
//
// I confirm that the content of this file is created by me,
// with the exception of the parts provided to me by my professor.
#include "Utilities.h"
#include <iostream>
char Utilities::m_delimiter = '\0';

void Utilities::setFieldWidth(size_t newWidth)
{

	m_widthField = 12;
}
size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{

	size_t pos = str.find_first_of(m_delimiter, next_pos);
	std::string out = str.substr(next_pos, pos - next_pos);
	if (!out.empty()) {
		next_pos = pos;
		setFieldWidth(30);
		more = true;
		return out;

	}
	else {
		more = false;
		throw std::string("Value Empty");
	}
}

std::string Utilities::extractToken2(const std::string& str, size_t& next_pos, bool& more) {
	size_t pos = str.find(m_delimiter, next_pos);
	if (pos == next_pos) {
		more = false;
		throw std::string("Value Empty");
	}
	else {
		more = pos != std::string::npos;
		std::string out = str.substr(next_pos, pos - next_pos);
		next_pos = pos + 1;
		if (out.size() > m_widthField)
			m_widthField = out.length();
		return out;
	}
}


void Utilities::setDelimiter(char newDelimiter)
{
	m_delimiter = newDelimiter;
}
char Utilities::getDelimiter()
{
	return m_delimiter;
}

