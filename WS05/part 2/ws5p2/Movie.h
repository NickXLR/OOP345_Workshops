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
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <iostream>
#include <string>


namespace sdds
{
	class Movie
	{
		std::string m_title{};
		size_t m_release{};
		std::string m_description{};

	public:
		Movie() = default;
		Movie(const std::string& strMovie);
		const std::string& title() const;
		std::ostream& print(std::ostream& out) const;
		//ASSUMPTION: In this design, type T must have an overload of the operator() that accepts a string as a parameter.
		template <typename T>
		void fixSpelling(T& spellChecker)
		{
			T(m_description);
		}

		friend std::ostream& operator<<(std::ostream& out, Movie& movie);
	};
}

#endif // !SDDS_MOVIE_H


