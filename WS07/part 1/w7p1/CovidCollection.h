/**********************************************************************************************************************************
				<assessment name: Workshop - #7 (Part-1)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: DATE

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#ifndef SDDS_COVID_COLLECTION_H
#define SDDS_COVID_COLLECTION_H
#include <string>
#include <vector>


namespace sdds
{
	struct Covid
	{
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		int m_year{};
		size_t m_cases{};
		size_t m_deaths{};
	};

	class CovidCollection
	{
		std::vector<Covid> m_coll{};

		void trimString(std::string& source);
	public:
		CovidCollection() = default;
		CovidCollection(const char* fileName);
		void display(std::ostream& out) const;
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}

#endif // !SDDS_COVID_COLLECTION_H


