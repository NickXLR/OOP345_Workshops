/**********************************************************************************************************************************
				<assessment name: Workshop - #4 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 10.4.23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#include <iostream>
#include "Cheese.h"
#include "CheeseParty.h"

using namespace sdds;
using namespace std;

void sdds::CheeseParty::emptyParty()
{
	for (size_t i = 0; i < m_numCheeses; i++)
	{
		m_pCheeses[i] = nullptr;
	}
	m_numCheeses = 0;
	m_pCheeses = nullptr;
}

sdds::CheeseParty::operator bool()
{
	return m_numCheeses != 0;
}

//sdds::CheeseParty::operator bool()
//{
//	return m_numCheeses != 0;
//}

void sdds::CheeseParty::removeCheeseAndShrink(const unsigned index)
{
	if (index < m_numCheeses)
	{
		const Cheese** newCheeseParty = new const Cheese * [m_numCheeses - 1];
		//deep copy except index
		for (size_t i = 0, j = 0; i < m_numCheeses - 1; i++, j++)
		{
			if (j == index)
			{
				j++;
			}
			newCheeseParty[i] = m_pCheeses[j];
		}

		//set m_pCheeses to new array
		delete[] m_pCheeses;
		m_pCheeses = newCheeseParty;
		m_numCheeses--;
	}
}

std::ostream& sdds::CheeseParty::print(std::ostream& out) const
{
	out << "--------------------------" << endl
		<< "Cheese Party" << endl
		<< "--------------------------" << endl;

	if (m_numCheeses != 0)
	{
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			out << *(m_pCheeses[i]);
		}
		out << "--------------------------" << endl;
	}
	else
	{
		out << "This party is just getting started!" << endl
			<< "--------------------------" << endl;
	}
	return out;
}


int sdds::CheeseParty::findEmptyCheese()
{
	int index = -1;
	bool found = false;

	for (size_t i = 0; i < m_numCheeses && !found; i++)
	{
		if (m_pCheeses[i]->getWeight() == 0u)
		{
			index = i;
			found = true;
		}
	}

	return index;
}

sdds::CheeseParty::CheeseParty(const CheeseParty& copy)
{
	*this = copy;
}

sdds::CheeseParty::CheeseParty(CheeseParty&& move) noexcept
{
	*this = std::move(move);
}

CheeseParty& sdds::CheeseParty::operator=(const CheeseParty& copy)
{
	if (this != &copy)
	{
		emptyParty();
		//deep copy
		m_numCheeses = copy.m_numCheeses;
		m_pCheeses = new const Cheese * [m_numCheeses];
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			m_pCheeses[i] = copy.m_pCheeses[i];
		}
	}

	return *this;
}

CheeseParty& sdds::CheeseParty::operator=(CheeseParty&& move) noexcept
{
	if (this != &move)
	{
		emptyParty();
		//take the resource
		m_numCheeses = move.m_numCheeses;
		m_pCheeses = new const Cheese * [m_numCheeses];
		m_pCheeses = move.m_pCheeses;
		move.m_pCheeses = nullptr;
		move.m_numCheeses = 0;
	}

	return *this;
}

sdds::CheeseParty::~CheeseParty()
{
	emptyParty();
}

CheeseParty& sdds::CheeseParty::addCheese(const Cheese& newCheese)
{
	//check if the cheese is already in party
	bool duplicate = false;

	for (size_t i = 0; i < m_numCheeses && !duplicate; i++)
		if (m_pCheeses[i] == &newCheese)
			duplicate = true;

	if (!duplicate)
	{
		//create new dynamically allocated array of pointers to Cheese objects with new size
		const Cheese** newCheeseParty = new const Cheese * [m_numCheeses + 1];
		//deep copy
		for (size_t i = 0; i < m_numCheeses; i++)
		{
			newCheeseParty[i] = m_pCheeses[i];
		}
		newCheeseParty[m_numCheeses] = &newCheese;

		//clear old and set to new
		delete[] m_pCheeses;
		m_pCheeses = newCheeseParty;
		m_numCheeses++;
	}

	return *this;
}

CheeseParty& sdds::CheeseParty::removeCheese()
{
	if (*this)
	{
		int emptyIndex{};
		bool foundEmpty = false;
		do
		{
			emptyIndex = findEmptyCheese();
			foundEmpty = emptyIndex >= 0;
			if (foundEmpty)
			{
				removeCheeseAndShrink(emptyIndex);
			}
		} while (foundEmpty);
	}

	return *this;
}

std::ostream& sdds::operator<<(std::ostream& out, const CheeseParty& cs)
{
	return cs.print(out);
}
