/**********************************************************************************************************************************
				<assessment name: Workshop - #4 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 10.5.23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/

#include <iostream>
#include <string>
#include "CheeseShop.h"

using namespace std;
using namespace sdds;

sdds::CheeseShop::CheeseShop()
{
	m_name = "No Name";
}

CheeseShop::CheeseShop(const string& name)
{
	m_name = name;
}

CheeseShop& sdds::CheeseShop::addCheese(const Cheese& addCheese)
{
	//creating a new cheese pointer and storing given cheese in it
	Cheese* newCheese = new Cheese;
	*newCheese = addCheese;
	//creating a new array thats 1 bigger
	Cheese** newArr = new Cheese * [m_numCheeses + 1];
	//copying from old array to new
	for (size_t i = 0; i < m_numCheeses; i++)
	{
		newArr[i] = new Cheese;
		*(newArr[i]) = *(m_cheeses[i]);
	}
	//adding the new one to new array
	newArr[m_numCheeses] = newCheese;
	//clearing current collection before taking new address
	emptyShop();
	//moving the address of the new array to member
	m_cheeses = newArr;
	m_numCheeses++;

	return *this;
}

void sdds::CheeseShop::emptyShop()
{
	if (*this)
	{
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			delete m_cheeses[i];
			m_cheeses[i] = nullptr;
		}
	}
	m_numCheeses = 0;
	delete[] m_cheeses;
	m_cheeses = nullptr;
}

sdds::CheeseShop::operator bool() const
{
	return m_cheeses != nullptr;
}

std::ostream& sdds::CheeseShop::print(std::ostream& out) const
{
	out << "--------------------------" << endl
		<< m_name << endl
		<< "--------------------------" << endl;

	if (*this)
	{
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			out << *(m_cheeses[i]);
		}
		out << "--------------------------" << endl;
	}
	else
	{
		out << "This shop is out of cheese!" << endl
			<< "--------------------------" << endl;
	}
	return out;
}

sdds::CheeseShop::CheeseShop(const CheeseShop& copy)
{
	operator=(copy);
}

sdds::CheeseShop::CheeseShop(CheeseShop&& move) noexcept
{
	*this = std::move(move);
}

CheeseShop& sdds::CheeseShop::operator=(const CheeseShop& copy)
{
	if (this != &copy)
	{
		emptyShop();
		m_name = copy.m_name;
		m_numCheeses = copy.m_numCheeses;
		m_cheeses = new Cheese * [m_numCheeses];

		for (size_t i = 0; i < m_numCheeses; i++)
		{
			m_cheeses[i] = new Cheese;
			*(m_cheeses[i]) = *(copy.m_cheeses[i]);
		}
	}

	return *this;
}

CheeseShop& sdds::CheeseShop::operator=(CheeseShop&& move) noexcept
{
	if (this != &move)
	{
		//take everything
		m_name = move.m_name;
		m_numCheeses = move.m_numCheeses;
		m_cheeses = move.m_cheeses;
		//leave nothing behind
		move.m_cheeses = nullptr;
		move.m_name = "";
	}

	return *this;
}

sdds::CheeseShop::~CheeseShop()
{
	emptyShop();
}

std::ostream& sdds::operator<<(std::ostream& out, const CheeseShop& cs)
{
	return cs.print(out);
}
