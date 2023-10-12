/**********************************************************************************************************************************
				<assessment name: Workshop - #5 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 10.4.23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>


namespace sdds
{
	class Book
	{
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{}; 
		double m_price{};
		std::string m_description{};

	public:
		Book() = default;
		Book(const std::string& strBook);
		const std::string& title() const;
		const std::string& coutry() const;
		const size_t& year() const;
		double& price();
		std::ostream& print(std::ostream& out);
		friend std::ostream& operator<<(std::ostream& out, Book& book);

		//ASSUMPTION: In this design, type T must have an overload of the operator() that accepts a string as a parameter.
		template <typename T>
		void fixSpelling(T& spellChecker)
		{
			T(m_description);
		}
	};

	std::string cutSpaces(std::string str);
}

#endif // !SDDS_BOOK_H





