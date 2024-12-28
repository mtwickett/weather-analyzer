// Ensure this header file is included only once
#pragma once

// standard library includes
#include <string>
#include <map>
#include <vector>
#include <iostream>


// create the Temperature class specification
class TemperatureRow
{
// declare the constructor using const as the values do not need to be altered 
// use call by reference so that copies 
public:
    TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures);
    
    std::string getTimestamp() const;
    std::string getYear() const;
    std::string getMonth() const;
    std::string getDay() const;

    void printRow();

    static const int getRowIndex(const std::vector<TemperatureRow>& rows,
        const std::string& timestamp);
    static const std::vector<TemperatureRow> getRowsByYear(const std::vector<TemperatureRow>& rows,
        const std::string& year);
    static const std::vector<TemperatureRow> getRowsByMonth(const std::vector<TemperatureRow>& rows,
        const std::string& month);
    static std::map <std::string, std::vector<double>> getTempsByYear(const std::vector<TemperatureRow>& rows,
        unsigned int countryIndex);
    static std::map <std::string, std::vector<double>> getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
        unsigned int countryIndex, std::string monthDay);
    

    std::string timestamp;
    std::vector<double> temperatures;

    static const std::map<std::string, int> years;
    static const std::map<std::string, unsigned int> countries;
};

