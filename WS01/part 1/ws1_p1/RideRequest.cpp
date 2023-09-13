/**********************************************************************************************************************************
				<assessment name: Workshop - #1 (Part-1)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 12-9-23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include "RideRequest.h"

using namespace sdds;
using namespace std;

double g_taxrate{};
double g_discount{};

RideRequest::RideRequest() : m_customerName{}, m_rideDesc{}, m_isDiscounted{}
{
}

RideRequest::~RideRequest()
{
	setEmpty();
}

sdds::RideRequest::operator bool() const
{
	return !(m_customerName[0] == '\0');
}

void sdds::RideRequest::setEmpty()
{
	m_customerName[0] = '\0';
}

std::istream& sdds::RideRequest::read(std::istream& input)
{
	if (input)//testing if istream is in good state
	{
		char tempName[CUSTOMER_NAME_MAX]{};
		char tempDesc[MAX_RIDE_DESC]{};
		double tempPrice{};
		char tempDiscount{};
		//Read name
		input.getline(tempName, CUSTOMER_NAME_MAX, ',');
		//Read description
		input.getline(tempDesc, MAX_RIDE_DESC, ',');
		//Read price
		input >> tempPrice;
		//ignore delimiter
		input.get();
		//Read discount
		input.get(tempDiscount);
		//get the newline
		//input.get();

		//check if reading succeeded
		if (input)
		{
			//Read successful, assign to members
			strcpy(m_customerName, tempName);
			strcpy(m_rideDesc, tempDesc);
			m_ridePrice = tempPrice;
			//cout << endl << "HAVE READ PRICE FOR " << m_customerName << " >" << tempPrice << "<" << endl;
			m_isDiscounted = (tempDiscount == 'Y') ? true : false;
		}
		else
		{
			//failed reading, destroy this object
			setEmpty();
		}
	}
	return input;
}

void sdds::RideRequest::display() const {
	static size_t count = 1;
	if (*this)
	{
		//calculate tax
		double priceWithTax = m_ridePrice * (1 + g_taxrate);

		//cout << endl << m_customerName << "'s PRICE IS: >" << m_ridePrice << "<" << endl;
		//cout << "AFTER TAX: >" << priceWithTax << "<" << endl;
		//cout << "TAX RATE: >" << g_taxrate << "<" << endl;

		cout << setw(2) << setiosflags(ios::left) << count << ". ";
		cout << setw(CUSTOMER_NAME_MAX) << m_customerName << '|';
		cout << setw(MAX_RIDE_DESC) << m_rideDesc << '|';
		cout << setw(12) << std::fixed << setprecision(2) << priceWithTax << '|' << resetiosflags(ios::left);
		//if discounted print discounted price
		if (m_isDiscounted)
		{
			double discountedPrice = priceWithTax - g_discount;
			cout << setiosflags(ios::right) << setw(13) << discountedPrice;
			cout << resetiosflags(ios::right);
		}
		cout << endl;
	}
	else
	{
		//no customer name
		cout << setw(2) << count << ". No Ride Request" << endl;
	}
	count++;
}

RideRequest& sdds::RideRequest::operator=(RideRequest& ro)
{
	if (ro)
	{	//if in good state copy all
		strcpy(m_customerName, ro.m_customerName);
		strcpy(m_rideDesc, ro.m_rideDesc);
		m_ridePrice = ro.m_ridePrice;
		m_isDiscounted = ro.m_isDiscounted;
	}
	else
	{	//otherwise destroy the object
		setEmpty();
	}
	
	return *this;
}
