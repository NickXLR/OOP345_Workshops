/**********************************************************************************************************************************
				<assessment name: Workshop - #3 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 27.9.23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H

#include "Collection.h"

namespace sdds
{
	template <typename T>
	class OrderedCollection : public Collection<T, 72u>
	{
	public:
		OrderedCollection() : Collection<T, 72u>() {};

		OrderedCollection(const OrderedCollection& oc) = delete;

		~OrderedCollection() = default;
		/// <summary>
		/// If possible, insert the item such that the collection is in ascending order
		/// </summary>
		/// <param name="ro">Item to insert</param>
		/// <returns>true if inserted</returns>
		bool operator+=(const T& ro)
		{
			if (this->size() < this->capacity())
			{
				this->incrSize();
				//inserting
				//if bigger than largest - place at the end
				if (ro > this->getLargestItem())
				{
					this->operator[](this->size()-1) = ro;
					this->setLargestItem(ro);
				}
				else//smaller than largest, will be placed either in the beginning or middle, will have to shift all items bigger than it up
				{
					//find index to place this item
					unsigned int targetIndex = 0u;
					bool foundTarget = false;
					for (unsigned i = 0u; i < this->size() && !foundTarget; i++)
					{
						if (this->operator[](i) > ro)
						{
							targetIndex = i;
							foundTarget = true;
						}
					}
					//shift all bigger eleemnts up and insert item
					for (unsigned i = (this->size() - 1); i > targetIndex; i--)
					{
						this->operator[](i) = this->operator[](i - 1);
					}
					this->operator[](targetIndex) = ro;
					
				}
				this->setSmallestItem(ro);
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}

#endif // !SDDS_ORDERED_COLLECTION_H
