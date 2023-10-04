#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include <string>
#include <iostream>

namespace sdds
{
	/// <summary>
	/// erase trailing and following spaces from given string and return new string
	/// </summary>
	/// <param name="str">string to chop chop</param>
	/// <returns>clean string</returns>
	std::string cutSpaces(std::string str);
	/// <summary>
	/// returns string up to the given delimiter
	/// </summary>
	/// <param name="str">what to cut</param>
	/// <param name="delim">where to cut</param>
	/// <returns>string after cutting</returns>
	std::string getStringUntilDelimiter(std::string str, char delim);
}

#endif // !SDDS_UTILS_H
