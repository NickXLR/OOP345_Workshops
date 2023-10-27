/**********************************************************************************************************************************
				<assessment name: Workshop - #6 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 27-10-23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <string>
#include "Directory.h"

namespace sdds
{
	class Filesystem
	{
		Directory* m_root{};
		Directory* m_current{};

		void addResource(std::string&,const std::string& = "");
	public:
		Filesystem(const char*, const std::string& = std::string());

		//copy operations not allowed
		Filesystem& operator=(Filesystem&) = delete;
		Filesystem(Filesystem&) = delete;

		//move operations
		Filesystem(Filesystem&&) noexcept;
		Filesystem& operator=(Filesystem&&) noexcept;

		//add a recourse to current directory
		Filesystem& operator+=(Resource*);

		//change current to given directory name
		Directory* change_directory(const std::string& = "");

		Directory* get_current_directory() const;

		~Filesystem();
	};

	std::string& trimString(std::string&);
}

#endif