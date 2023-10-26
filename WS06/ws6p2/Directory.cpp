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
		for (auto i = 0; i < m_contents.size() && !dupe; i++)
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


		for (auto item : m_contents)
		{
			if (item->type() == NodeType::FILE && item->name() == name)
			{
				result = item;
			}
			if (recursive && item->type() == NodeType::DIR)
			{
				result = dynamic_cast<Directory*>(item)->find(name, flags);
			}
		}


		return result;
	}
	Directory::~Directory()
	{
		for (auto item : m_contents)
			delete item;
	}
	std::string Directory::name() const
	{
		return m_name;
	}
}