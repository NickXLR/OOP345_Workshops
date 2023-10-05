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


#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include "Cheese.h"

namespace sdds
{
	class CheeseParty
	{
		const Cheese** m_pCheeses{};
		unsigned m_numCheeses{};
	public:
		CheeseParty() = default;

		void emptyParty();
		operator bool();

		/// <summary>
		/// removes a cheese by index and shrinks m_pCheeses accordingly
		/// </summary>
		/// <param name="index"></param>
		void removeCheeseAndShrink(const unsigned index);

		std::ostream& print(std::ostream& out) const;

		/// <summary>
		/// return first index of empty cheese, otherwise -1
		/// </summary>
		/// <returns>index of empty cheese or -1</returns>
		int findEmptyCheese();

		//rule of 5
		CheeseParty(const CheeseParty& copy);
		CheeseParty(CheeseParty&& move) noexcept;
		CheeseParty& operator=(const CheeseParty& copy);
		CheeseParty& operator=(CheeseParty&& move) noexcept;
		~CheeseParty();

		CheeseParty& addCheese(const Cheese& newCheese);
		CheeseParty& removeCheese();
	};

	std::ostream& operator<<(std::ostream& out, const CheeseParty& cs);
}

#endif // !SDDS_CHEESEPARTY_H



