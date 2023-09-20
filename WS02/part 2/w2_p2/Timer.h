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
#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>

namespace sdds
{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> m_start{};
		std::chrono::time_point<std::chrono::steady_clock> m_end{};
	public:
		void start();
		long long int stop();
	};

}

#endif // !SDDS_TIMER_H



