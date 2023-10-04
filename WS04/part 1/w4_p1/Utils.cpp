#include <string>
#include <iostream>
#include "Utils.h"

std::string sdds::cutSpaces(std::string str)
{
    unsigned i = 0;

    //erasing trailing spaces
    while (isspace(str[i]) && i < str.length())
        i++;

    str = str.erase(0, i);

    //erasing following spaces
    i = 0;
    while (!(isspace(str[i]) && isspace(str[i + 1])) && i < str.length())
        i++;

    str = str.erase(i, str.length());

    return str;
}

std::string sdds::getStringUntilDelimiter(std::string str, char delim)
{
    unsigned end = str.find_first_of(delim);
    return str.substr(0, end);
}
