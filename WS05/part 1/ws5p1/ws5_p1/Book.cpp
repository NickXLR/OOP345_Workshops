/**********************************************************************************************************************************
				<assessment name: Workshop - #5 (Part-1)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: DATE

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"


using namespace std;
namespace sdds
{
	Book::Book(const std::string& strBook)
	{
		string temp{};
		string copy = strBook;
		size_t delim{};

		//get Book author
		delim = copy.find_first_of(',');
		temp = copy.substr(0, delim);
		m_author = cutSpaces(temp);
		copy.erase(0, delim + 1);

		//get Book title
		delim = copy.find_first_of(',');
		temp = copy.substr(0, delim);
		m_title = cutSpaces(temp);
		copy.erase(0, delim + 1);

		//get Book country
		delim = copy.find_first_of(',');
		temp = copy.substr(0, delim);
		m_country = cutSpaces(temp);
		copy.erase(0, delim + 1);

		//get Book price
		delim = copy.find_first_of(',');
		temp = copy.substr(0, delim);
		temp = cutSpaces(temp);
		m_price = stod(temp);
		copy.erase(0, delim + 1);

		//get Book year
		delim = copy.find_first_of(',');
		temp = copy.substr(0, delim);
		temp = cutSpaces(temp);
		m_year = stoi(temp);
		copy.erase(0, delim + 1);

		//get Book description
		delim = copy.find_first_of('\n');
		temp = copy.substr(0, delim);
		m_description = cutSpaces(temp);
	}
	const std::string& Book::title() const
	{
		return m_title;
	}
	const std::string& Book::coutry() const
	{
		return m_country;
	}
	const size_t& Book::year() const
	{
		return m_year;
	}
	double& Book::price()
	{
		return m_price;
	}

	std::ostream& Book::print(std::ostream& out)
	{
		out << setw(20) << m_author << " | "
			<< setw(22) << m_title << " | "
			<< setw(5) << m_country << " | "
			<< setw(4) << m_year << " | "
			<< setw(6) << setprecision(2) << setiosflags(ios::fixed) << m_price << " | "
			<< m_description;

		return out;
	}

	std::ostream& operator<<(std::ostream& out, Book& book)
	{
		return book.print(out);
	}

	string cutSpaces(string str)
	{
		unsigned i = 0;

		//erasing trailing spaces
		while (isspace(str[i]) && i < str.length())
			i++;

		str = str.erase(0, i);

		//erasing following spaces
		i = 0;
		while (!(isspace(str[i]) && isspace(str[i + 1])) && i < str.length())
			i++;

		str = str.erase(i, str.length());

		return str;
	}
}