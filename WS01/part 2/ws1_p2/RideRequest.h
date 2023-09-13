/**********************************************************************************************************************************
				<assessment name: Workshop - #1 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 12-9-23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

extern double g_taxrate;
extern double g_discount;

const int CUSTOMER_NAME_MAX = 10;
const int MAX_RIDE_DESC = 25;

namespace sdds
{
	class RideRequest
	{
		char m_customerName[CUSTOMER_NAME_MAX]{};
		char* m_rideDesc{};//Dynamic c type string
		double m_ridePrice{};
		bool m_isDiscounted{};
	public:
		RideRequest();
		RideRequest(RideRequest& copy);
		~RideRequest();
		/// <summary>
		/// Read name, desc and boolean if discounted from given istream
		/// </summary>
		/// <param name="input">where to read from</param>
		/// <returns>same istream that was passed</returns>
		std::istream& read(std::istream& input);
		/// <summary>
		/// display counter and contents of the object to cout
		/// </summary>
		void display() const;
		/// <summary>
		/// copy assignment operator
		/// </summary>
		/// <param name="ro">what to assign</param>
		/// <returns>object after assigning</returns>
		RideRequest& operator=(RideRequest& ro);
	private:
		/// <summary>
		/// Return true if name populated
		/// </summary>
		operator bool()const;
		/// <summary>
		/// sets current object to empty state
		/// </summary>
		void setEmpty();
		/// <summary>
		/// setter for dynamic description
		/// </summary>
		/// <param name="size">how big you want it</param>
		/// <param name="source"></param>
		void setRideDescription(size_t size, const char* source);
	};


}

#endif // !
