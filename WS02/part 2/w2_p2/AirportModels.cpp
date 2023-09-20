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
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "AirportModels.h"

using namespace sdds;
using namespace std;

sdds::Airport::operator bool() const
{
    return m_airportCode.length() != 0;
}

std::ostream& sdds::Airport::print(std::ostream& out) const
{
    if (*this) 
    {
        printLabel(out, "Airport Code");
        printValue(out, m_airportCode);

        printLabel(out, "Airport Name");
        printValue(out, m_airportName);

        printLabel(out, "City");
        printValue(out, m_airportCity);

        printLabel(out, "State");
        printValue(out, m_airportState);

        printLabel(out, "Country");
        printValue(out, m_airportCoutry);

        printLabel(out, "Latitude");
        printValue(out, m_latitude);

        printLabel(out, "Longitude");
        printValue(out, m_longitude);
    }
    else
    {
        out << "Empty Airport";
    }
    return out;
}

void sdds::Airport::set(const std::string airportCode,
    const std::string airportName,
    const std::string airportCity,
    const std::string airportState,
    const std::string airportCoutry,
    const double latitude,
    const double longitude)
{
    m_airportCode = airportCode;
    m_airportName = airportName;
    m_airportCity = airportCity;
    m_airportState = airportState;
    m_airportCoutry = airportCoutry;
    m_latitude = latitude;
    m_longitude = longitude;
}

void sdds::Airport::set(const Airport& copy)
{
    if (copy)
    {
        m_airportCode = copy.m_airportCode;
        m_airportName = copy.m_airportName;
        m_airportCity = copy.m_airportCity;
        m_airportState = copy.m_airportState;
        m_airportCoutry = copy.m_airportCoutry;
        m_latitude = copy.m_latitude;
        m_longitude = copy.m_longitude;
    }
}


std::ostream& sdds::operator<<(std::ostream& out, const Airport& airPort)
{
    return airPort.print(out);
}

std::ostream& sdds::printLabel(std::ostream& out, const string& str)
{
    return out << setiosflags(ios::right) << setw(20) << setfill('.') << str << " : " << resetiosflags(ios::right);
}

std::ostream& sdds::printValue(std::ostream& out, const string& str)
{
    return out << setiosflags(ios::left) << setw(30) << setfill('.') << str << resetiosflags(ios::left) << endl;
}

std::ostream& sdds::printValue(std::ostream& out, const double& val)
{
    return out << setiosflags(ios::left) << setw(30) << setfill('.') << val << resetiosflags(ios::left) << endl;
}

int sdds::AirportLog::loadAirports(const char* fileName)
{
    //flag thats 1 if load is successful
    int loaded = 1;
    ifstream airportsFile(fileName);
    string code{};
    string name{};
    string city{};
    string state{};
    string country{};
    double latitude{};
    double longitude{};

    //ignore first line (headers)
    getline(airportsFile, code, '\n');
    code = "";

    //read a line for every m_count
    for (size_t i = 0; i < m_count && loaded; i++)
    {
        getline(airportsFile, code, ',');
        getline(airportsFile, name, ',');
        getline(airportsFile, city, ',');
        getline(airportsFile, state, ',');
        getline(airportsFile, country, ',');
        airportsFile >> latitude;
        airportsFile.get(); //getting delimiter
        airportsFile >> longitude;
        airportsFile.get(); //getting newline

        if (!airportsFile.fail())
        {
            m_airPorts[i].set(code, name, city, state, country, latitude, longitude);
        }
        else
        {
            //cout << "line count is: " << i << " but loaded became 0" << endl;
            loaded = 0;
        }
        
    }

    return loaded;
}

void sdds::AirportLog::setEmpty()
{
    delete[] m_airPorts;
    m_airPorts = nullptr;
    m_count = 0;
}

sdds::AirportLog::AirportLog()
{
    m_airPorts = nullptr;
    m_count = 0u;
}

sdds::AirportLog::AirportLog(const char* fileName)
{
    //one less to ignore first line
    m_count = getFileNumRows(fileName) - 1;
    
    if (m_count)
    {
        //allocating space for the number of airports in the file
        m_airPorts = new Airport[m_count];
        //if load was unsuccesful, set object to empty
        if (!loadAirports(fileName))
        {
            setEmpty();
        }
    }

}

void sdds::AirportLog::addAirport(const Airport& toAdd)
{
    //if the airport to add isnt empty, add it
    if (toAdd)
    {
        //create new array with size + 1
        Airport* newAirports = new Airport[m_count + 1];
        //deep copy
        for (size_t i = 0; i < m_count; i++)
        {
            newAirports[i] = m_airPorts[i];
        }
        //add the new one
        newAirports[m_count] = toAdd;
        //increase count
        m_count++;
        //delete previous array
        delete[] m_airPorts;
        //set to new
        m_airPorts = newAirports;
    }
}

sdds::AirportLog::operator bool()
{
    return m_count && (m_airPorts != nullptr);
}

AirportLog sdds::AirportLog::findAirport(const char* state, const char* country) const
{
    AirportLog result{};
    for (size_t i = 0; i < m_count; i++)
    {
        //cout << "Comparing >" << state << "< to >" << m_airPorts[i].m_airportState.c_str() << "< and >" << country << "< to >" << m_airPorts[i].m_airportCoutry.c_str() << endl;
        int stateMatch = strcmp(m_airPorts[i].m_airportState.c_str(), state);
        int countryMatch = strcmp(m_airPorts[i].m_airportCoutry.c_str(), country);
        if (!stateMatch && !countryMatch)
        {
            result += m_airPorts[i];
        }
    }
    return result;
}

AirportLog& sdds::AirportLog::operator+=(const Airport& ro)
{
    addAirport(ro);
    return *this;
}

Airport sdds::AirportLog::operator[](size_t index)
{
    Airport ret{};
    if (index < m_count)
    {
        ret = m_airPorts[index];
    }
    return ret;
}

sdds::AirportLog::operator size_t()
{
    return m_count;
}

sdds::AirportLog::AirportLog(const AirportLog& copy)
{
    *this = copy;
}

sdds::AirportLog::AirportLog(AirportLog&& move)noexcept
{
    //take the recource instead of copying for rvalue reference
    m_count = move.m_count;
    m_airPorts = move.m_airPorts;
    move.m_airPorts = nullptr;
    move.m_count = 0;
}

AirportLog& sdds::AirportLog::operator=(const AirportLog& copy)
{
    //will only copy if objects are not the same
    if (this != &copy)
    {
        if (*this)
        {//if this object has a resource remove it
            setEmpty();
        }
        m_count = copy.m_count;
        m_airPorts = new Airport[m_count];
        for (size_t i = 0; i < m_count; i++)
        {
            m_airPorts[i] = copy.m_airPorts[i];
        }
    }
    return *this;
}

AirportLog& sdds::AirportLog::operator=(AirportLog&& move)noexcept
{
    //will only copy if objects are not the same
    if (this != &move)
    {
        if (*this)
        {//if this object has a resource remove it
            setEmpty();
        }
        m_count = move.m_count;
        //take the recource instead of copying for rvalue reference
        m_airPorts = move.m_airPorts;
        move.m_airPorts = nullptr;
        move.m_count = 0;
    }
    return *this;
}

sdds::AirportLog::~AirportLog()
{
    setEmpty();
}

size_t sdds::getFileNumRows(const char* fileName)
{
    size_t file_size = 0u;
    ifstream airportsFile(fileName);
    string line{};

    if (airportsFile)
    {
        //count number of lines in file
        while (getline(airportsFile, line))
        {
            file_size++;
        }
    }

    //will return 0 if couldnt open file
    return file_size;
}