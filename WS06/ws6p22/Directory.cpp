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
#include <iostream>
#include <iomanip>
#include "Directory.h"


namespace sdds
{
	sdds::Directory::Directory(std::string dir)
	{
		m_name = dir;
	}

	void sdds::Directory::update_parent_path(const std::string& dir)
	{
		m_parent_path = dir;
		for (auto item : m_contents)
		{
			item->update_parent_path(dir + m_name);
		}
	}

	NodeType sdds::Directory::type() const
	{
		return NodeType::DIR;
	}

	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}
	int Directory::count() const
	{
		return (int)m_contents.size();
	}
	size_t Directory::size() const
	{
		size_t size{};
		if (m_contents.size())
		{
			for (auto item : m_contents)
				size += item->size();
		}
		return size;
	}
	Directory& Directory::operator+=(Resource* toAdd)
	{
		bool dupe = false;
		//check weather such an item exists
		for (size_t i = 0; i < m_contents.size() && !dupe; i++)
		{
			if (toAdd->name() == m_contents[i]->name())
				dupe = true;
		}
		//add if not duplicate, else throw exception
		if (!dupe)
		{
			m_contents.push_back(toAdd);
			toAdd->update_parent_path(m_parent_path + m_name);
		}
		else 
		{
			throw "Duplicate insertion of resource into directory";
		}

		return *this;
	}
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
	{
		Resource* result = nullptr;
		bool recursive = false;
		//check if recursive flag received
		for (auto flag : flags)
			if (flag == OpFlags::RECURSIVE)
				recursive = true;


		for (size_t i = 0; i < m_contents.size() && result == nullptr; i++)
		{
			if (m_contents[i]->name() == name)
			{
				result = m_contents[i];
			}
			else if (recursive && m_contents[i]->type() == NodeType::DIR)
			{
				result = dynamic_cast<Directory*>(m_contents[i])->find(name, flags);
			}
		}

		return result;
	}
	Directory::~Directory()
	{
		for (auto item : m_contents)
			delete item;
	}
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
	{
		bool recursive = false;
		//check if recursive flag received
		for (auto flag : flags)
			if (flag == OpFlags::RECURSIVE)
				recursive = true;

		Resource* result = find(name, flags);
		if (result) //result was found
		{
			//find index of result
			size_t resultIndex{};
			for (size_t i = 0; i < m_contents.size(); i++)
			{
				if (m_contents[i] == result)
					resultIndex = i;
			}

			if (result->type() == NodeType::DIR) //result is a directory
			{
				if (recursive)
				{
					delete result;
					result = nullptr;
					m_contents.erase(m_contents.begin() + resultIndex);
				}
				else
				{
					throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
				}
			}
			else if (result->type() == NodeType::FILE) //result is a file
			{
				delete result;
				result = nullptr;
				m_contents.erase(m_contents.begin() + resultIndex);
			}
			else //unknown result type
			{
				throw "Found unknown result type when searching resource to remove";
			}
		}
		else//no result found
		{
			throw name + std::string(" does not exist in ") + m_parent_path;
		}
	}
	void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const
	{
		bool longFlag = false;
		for (auto flag : flags)
			if (flag == FormatFlags::LONG)
				longFlag = true;

		os << "Total size: " << std::setw(2) << size() << " bytes\n";

		for (auto res : m_contents)
		{
			if (res->type() == NodeType::FILE)
			{
				os << "F | " << std::setw(15) << std::setiosflags(std::ios::left) << res->name() << " |";
			}
			else if (res->type() == NodeType::DIR) 
			{
				os << "D | " << std::setw(15) << std::setiosflags(std::ios::left) << res->name() << " |";
			}
			if (longFlag)
			{
				if (res->type() == NodeType::FILE)
				{
					os << "  " << std::setw(2) << "" << "|" << std::setw(5) <<  std::setiosflags(std::ios::right) << res->size() << " bytes |";
				}
				else if (res->type() == NodeType::DIR)
				{
					os << "  " << std::setw(2) << std::resetiosflags(std::ios::right) << res->count() << "|" << std::setw(5) << std::setiosflags(std::ios::right) << res->size() << " bytes |";
				}
				//os << std::resetiosflags(std::ios::right) << "";
			}
			os << std::endl;
		}
	}
	std::string Directory::name() const
	{
		return m_name;
	}
}