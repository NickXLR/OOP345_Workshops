#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>
#include "Book.h"

namespace sdds
{

	template <typename T, const unsigned C>
	class Collection
	{
		const unsigned m_capacity = C;
		unsigned m_size{};
		T m_items[C]{};
		static T m_smallestItem{};
		static T m_largestItem{};
	protected:
		/// <summary>
		/// sets smallest item to received item if its smaller
		/// </summary>
		/// <param name="item">item to set</param>
		void setSmallestItem(const T& item) 
		{
			if (m_smallestItem > item)
			{
				m_smallestItem = item;
			}
		}
		/// <summary>
		/// sets biggest item if received item is bigger
		/// </summary>
		/// <param name="item">item to set</param>
		void setLargestItem(const T& item) 
		{
			if (m_largestItem < item)
			{
				m_largestItem = item;
			}
		}
	public:
		/// <summary>
		/// defauld constructor
		/// </summary>
		Collection() : m_items{}, m_size{} {}
		/// <summary>
		/// copy constructor is prohibited, class is to only be instantiated with default constructor
		/// </summary>
		/// <param name=""></param>
		Collection(const Collection&) = delete;
		/// <summary>
		/// retruns current smallest item
		/// </summary>
		/// <returns></returns>
		static T getSmallestItem()
		{
			return m_smallestItem;
		}
		/// <summary>
		/// returns current largest item
		/// </summary>
		/// <returns></returns>
		static T getLargestItem() 
		{
			return m_largestItem;
		}
		/// <summary>
		/// return current size
		/// </summary>
		unsigned size() const
		{
			return m_size;
		}
		/// <summary>
		/// return current capacity
		/// </summary>
		unsigned capacity() const
		{
			return m_capacity;

		}
		/// <summary>
		/// returns true if theres anything in collection
		/// </summary>
		operator bool() const
		{
			return m_size;
		}
		/// <summary>
		/// adds received item to collection if theres space for it
		/// </summary>
		/// <param name="ro">item to add</param>
		/// <returns>true if added</returns>
		bool operator+=(const T& ro)
		{
			if (m_size < m_capacity)
			{
				setSmallestItem(ro);
				setLargestItem(ro);
				m_items[m_size] = ro;
				m_size++;
				return true;
			}
			else
			{
				return false;
			}
		}

		void print(std::ostream& out) const
		{
			if (*this)
			{
				//out << "(smallest,largest) items: ("
				//	<< m_smallestItem << ","
				//	<< m_largestItem << ")" << std::endl;
				//out << "size/capacity: " << m_size
				//	<< "/" << m_capacity << std::endl;
				out << '[';
				for (size_t i = 0u; i < m_size; i++)
				{
					out << m_items[i] << ((i == (m_size - 1)) ? ']' : ',');
				}
				out << std::endl;
			}
		}
	};

	//initializing smallest and biggest item for general collection
	template <typename T,const unsigned C>
	T Collection<T,C>::m_smallestItem = 9999;
	template <typename T,const unsigned C>
	T Collection<T,C>::m_largestItem = -9999;

	//Book specialization
	template <>
	Book Collection<Book,10>::m_smallestItem("",1,1000);
	template <>
	Book Collection<Book, 10>::m_largestItem("", 10000, 1);

	//template <typename T, const unsigned C>
	//void Collection<T, C>::print(std::ostream& out) const
	//{
	//	//out << "PRINTING CONTENTS NOW" << std::endl;
	//	if (*this)
	//	{
	//		//out << "(smallest,largest) items: ("
	//		//	<< m_smallestItem << ","
	//		//	<< m_largestItem << ")" << std::endl;
	//		//out << "size/capacity: " << m_size
	//		//	<< "/" << m_capacity << std::endl;
	//		//out << "Contents: [";
	//		for (size_t i = 0u; i < m_size; i++)
	//		{
	//			out << i;
	//			out << m_items[i] << ((i == (m_size - 1)) ? "," : "]");
	//		}
	//		out << "FIRST ITEM IS: " << m_items[0] << std::endl;
	//		out << std::endl;
	//	}
	//}
}

#endif // !SDDS_COLLECTION_H
