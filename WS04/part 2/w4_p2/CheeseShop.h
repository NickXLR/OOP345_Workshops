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

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>
#include "Cheese.h"

namespace sdds
{
	class CheeseShop
	{
		std::string m_name{};
		unsigned m_numCheeses{};
		const Cheese** m_cheeses{};	//Dynamically allocated array of dynamically allocated cheeses

	public:
		CheeseShop();
		CheeseShop(const std::string& name);
		CheeseShop& addCheese(const Cheese& addCheese);
		/// <summary>
		/// rats ate all the cheese
		/// </summary>
		void emptyShop();
		/// <summary>
		/// have you got any cheese?
		/// </summary>
		operator bool() const;

		std::ostream& print(std::ostream& out) const;

		//rule of 5
		CheeseShop(const CheeseShop& copy);
		CheeseShop(CheeseShop&& move) noexcept;
		CheeseShop& operator=(const CheeseShop& copy);
		CheeseShop& operator=(CheeseShop&& move) noexcept;
		~CheeseShop();

	};

	std::ostream& operator<<(std::ostream& out, const CheeseShop& cs);

}
#endif // !SDDS_CHEESESHOP_H
