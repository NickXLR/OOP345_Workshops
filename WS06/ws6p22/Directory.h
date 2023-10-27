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
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <iostream>
#include <vector>
#include <string>
#include "Resource.h"



namespace sdds
{
	class Directory : public Resource
	{
		std::vector<Resource*> m_contents{};
	public:
		Directory(std::string dir);
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
		Directory& operator+=(Resource*);
		Resource* find(const std::string&, const std::vector<OpFlags>& = {});
		~Directory();

		//copy and move not allowed
		Directory(const Directory&) = delete;
		Directory(const Directory&&) = delete;
		Directory& operator=(const Directory&) = delete;
		Directory& operator=(const Directory&&) = delete;

		//part 2 additions
		void remove(const std::string&, const std::vector<OpFlags> & = {});

		void display(std::ostream&, const std::vector<FormatFlags>& = {}) const;
	};
}

#endif