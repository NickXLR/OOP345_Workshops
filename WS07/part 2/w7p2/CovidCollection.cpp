/**********************************************************************************************************************************
				<assessment name: Workshop - #7 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 7-11-23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
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

				//wish that would work :(
				//file >> newCov.m_country >> newCov.m_city >> newCov.m_variant >> tempYear >> tempCases >> tempDeaths;

				//add the new covid to collection
				m_coll.push_back(newCov);
			}
		}
		else //file could not be reached raise exception
		{
			throw "File could not be reached";
		}
	}

	void CovidCollection::display(std::ostream& out, const std::string& country) const
	{
		size_t totalCases{};
		size_t totalDeaths{};

		if (country == "ALL")
		{
			for_each(m_coll.begin(), m_coll.end(), [=,&out, &totalCases, &totalDeaths](Covid cov) 
				{
					out << cov << endl;
					totalCases += cov.m_cases;
					totalDeaths += cov.m_deaths;
				});
			out << "|" << setw(80) << setiosflags(ios::right) << "Total cases around the world: " << totalCases << " |\n"
				<< "|" << setw(80) << "Total deaths around the world: " << totalDeaths << " |\n" << resetiosflags(ios::right);
		}
		else
		{
			size_t localCases{};
			size_t localDeaths{};
			stringstream TotCases{};
			stringstream TotDeaths{};
			stringstream TotPercent{};
			out << "Displaying information of country = " << country << "\n";
			for_each(m_coll.begin(), m_coll.end(), [=, &out, &totalCases, &totalDeaths, &localCases, &localDeaths](Covid cov)
				{
					totalCases += cov.m_cases;
					totalDeaths += cov.m_deaths;
					if (cov.m_country == country)
					{
						out << cov << endl;;
						localCases += cov.m_cases;
						localDeaths += cov.m_deaths;
					}
				});
			TotCases << "Total cases in " << country << ": " << localCases;
			out << "|" << setw(85) << setiosflags(ios::right) << TotCases.str() << " |\n";
			TotDeaths << "Total deaths in " << country << ": " << localDeaths;
			out << "|" << setw(85) << TotDeaths.str() << " |\n";
			TotPercent << country << " has " << setprecision(6) << setiosflags(ios::fixed) << ((double)localCases / totalCases) * 100 << "% of global cases and " << ((double)localDeaths / totalDeaths) * 100 << "% of global deaths";
			out	<< "|" << setw(85) << TotPercent.str() << " |\n"
				<< resetiosflags(ios::right);
		}
	}

	void CovidCollection::sort(const std::string& field)
	{
		if (field == "city")
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_city.compare(b.m_city) < 0)
				{
					return true;
				}
				else if (a.m_city.compare(b.m_city) > 0)
				{
					return false;
				}
				else //they are the same
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				});
		}
		else if (field == "variant")
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_variant.compare(b.m_variant) < 0)
				{
					return true;
				}
				else if (a.m_variant.compare(b.m_variant) > 0)
				{
					return false;
				}
				else //they are the same
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				});
		}
		else if (field == "year")
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_year > b.m_year)
				{
					return true;
				}
				else if (a.m_year < b.m_year)
				{
					return false;
				}
				else
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				});
		}
		else if (field == "cases") 
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_cases > b.m_cases)
				{
					return true;
				}
				else if (a.m_cases < b.m_cases)
				{
					return false;
				}
				else
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				});
		}
		else if (field == "deaths")
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_deaths > b.m_deaths)
				{
					return true;
				}
				else
				{
					return false;
				}
				});
		}
		else if (field == "severity")
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_severity.compare(b.m_severity) < 0)
				{
					return true;
				}
				else if (a.m_severity.compare(b.m_severity) > 0)
				{
					return false;
				}
				else //they are the same
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				});
		}
		else //country
		{
			std::sort(m_coll.begin(), m_coll.end(), [=](const Covid& a, const Covid& b) {
				if (a.m_country.compare(b.m_country) < 0)
				{
					return true;
				}
				else if (a.m_country.compare(b.m_country) > 0)
				{
					return false;
				}
				else //they are the same
				{
					if (a.m_deaths < b.m_deaths)
					{
						return true;
					}
					else 
					{
						return false;
					}
				}
				});
		}
	}

	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		return 
			any_of(m_coll.begin(), m_coll.end(), [=](const Covid& cov) {
			return cov.m_variant == variant && cov.m_country == country && cov.m_deaths > deaths;
			});
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		list<Covid> list{};
		copy_if(m_coll.begin(), m_coll.end(), std::back_inserter(list),[=](const Covid& cov) -> bool
			{
				return cov.m_deaths >= deaths;
			});
		return list;
	}

	void CovidCollection::updateStatus()
	{
		//vector<Covid> copy{};
		transform(m_coll.begin(), m_coll.end(), m_coll.begin(), [](const Covid& cov) {
			Covid newCov = cov;
			if (cov.m_deaths > EPIDEMIC_DEATHS)
				newCov.m_severity = "EPIDEMIC";
			else if(cov.m_deaths < EARLY_DEATHS)
				newCov.m_severity = "EARLY";
			else
				newCov.m_severity = "MILD";
			return newCov;
			});
		//std::copy(copy.begin(), copy.end(), m_coll.begin());
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
				<< setw(3) << theCovid.m_deaths << " | "
				<< "| " << setw(8) << theCovid.m_severity << " |";

		return out;
	}
	bool operator<(const std::string& a, const std::string& b)
	{
		return false;
	}
}
