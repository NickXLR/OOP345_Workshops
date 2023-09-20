/**********************************************************************************************************************************
				<assessment name: Workshop - #2 (Part-2)>
Full Name  : Nikolay Gofstein
Student ID#: 182368217
Email      : ngofstein@myseneca.ca
Section    :  ZAA
Date of Completion: 19.9.23

Authenticity Declaration:
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
***********************************************************************************************************************************/
#include <chrono>
#include "Timer.h"

using namespace std;
using namespace chrono;
using namespace sdds;

void sdds::Timer::start()
{
	//set start to the time at call
	m_start = std::chrono::system_clock::now();
}

long long int sdds::Timer::stop()
{
	//get time at stop
	m_end = std::chrono::system_clock::now();
	//calculate and store difference between start and stop
	auto chrono_duration = duration_cast<nanoseconds>(m_end - m_start);

	long long int duration = chrono_duration.count();
	
	return duration;
}
