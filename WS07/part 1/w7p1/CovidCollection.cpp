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
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include "CovidCollection.h"

using namespace std;
namespace sdds
{
	sdds::CovidCollection::CovidCollection(const char* fileName)
	{
		fstream file(fileName);

		if (file)
		{
			//extract covid details from file
			while (file.peek() != EOF) 
			{
				Covid newCov{};
				string tempYear{};
				string tempCases{};
				string tempDeaths{};
				char temp[26]{};
				char tempNum[6]{};

				//read country
				file.read(temp, 25);
				newCov.m_country = temp;
				trimString(newCov.m_country);

				//read city
				file.read(temp, 25);
				newCov.m_city = temp;
				trimString(newCov.m_city);

				//read variant
				file.read(temp, 25);
				newCov.m_variant = temp;
				trimString(newCov.m_variant);

				//read year
				file.read(tempNum, 5);
				tempYear = tempNum;
				trimString(tempYear);
				newCov.m_year = stoi(tempYear);

				//read cases
				file.read(tempNum, 5);
				tempCases = tempNum;
				trimString(tempCases);
				newCov.m_cases = stoul(tempCases);

				//read deaths
				file >> tempDeaths;
				trimString(tempDeaths);
				newCov.m_deaths = stoul(tempDeaths);

				//ignore everything else untill newline
				file.ignore(numeric_limits<std::streamsize>::max(),'\n');
				//file >> newCov.m_country >> newCov.m_city >> newCov.m_variant >> tempYear >> tempCases >> tempDeaths;
				// 
				//add the new covid to collection
				m_coll.push_back(newCov);
			}
		}
		else //file could not be reached raise exception
		{
			throw "File could not be reached";
		}
	}

	void CovidCollection::display(std::ostream& out) const
	{
		for_each(m_coll.begin(), m_coll.end(), [&out](Covid cov) {out << cov;});
	}

	void CovidCollection::trimString(std::string& source)
	{
		size_t begin = source.find_first_not_of(" \t\n");
		size_t end = source.find_last_not_of(" \t\n");
		string res{};
		if (begin != string::npos && end != string::npos)
		{
			res = source.substr(begin, end - begin + 1);
		}
		else
		{
			res = "";
		}
		source = res;
	}
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << setw(21) << std::left << theCovid.m_country << " | "
			<< setw(15) << theCovid.m_city << " | "
			<< setw(20) << theCovid.m_variant << " | " << resetiosflags(ios::left)
			<< setw(6);
			//print the year if positive
			if (theCovid.m_year > 0)
				out << theCovid.m_year << " | ";
			else
				out << " " << " | ";

			out << setw(4) << theCovid.m_cases << " | "
			<< setw(3) << theCovid.m_deaths << " |"
			<< endl;

		return out;
	}
}
