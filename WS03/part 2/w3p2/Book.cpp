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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Book.h"

using namespace std;
using namespace sdds;

std::ostream& sdds::operator<<(std::ostream& os, const Book& bk)
{
    return bk.print(os);
}

Book::Book() {}

Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
{
    m_title = title;
    m_numChapters = nChapters;
    m_numPages = nPages;
}

Book::operator bool() const
{
    return m_title.length();
}

bool sdds::Book::operator<(const Book& ro) const
{
    return ((double)m_numPages / m_numChapters) < ((double)ro.m_numPages / ro.m_numChapters);
}

bool sdds::Book::operator>(const Book& ro) const
{
    return ((double)m_numPages / m_numChapters) > ((double)ro.m_numPages / ro.m_numChapters);
}

std::ostream& Book::print(std::ostream& os) const
{
    //if obj in good state print its data
    if (*this)
    {
        stringstream ss;
        ss << m_title << "," << m_numChapters << "," << m_numPages << " | (";
        os << setw(60) << setiosflags(ios::right) << ss.str();
        os << setprecision(6) << resetiosflags(ios::right)
           << setiosflags(ios::left) << setiosflags(ios::fixed)
           << ((double)m_numPages / m_numChapters) << ")    ";
        os << resetiosflags(ios::fixed);
    }
    else {
        os << "| Invalid book data";
    }
    
    return os;
}
