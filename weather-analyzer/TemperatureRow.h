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
// use call by reference so that copies are not made
public:
    TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures);

    const std::vector<double>& getTemperatures() const;

    static const int getRowIndex(const std::vector<TemperatureRow>& rows,
        const std::string& timestamp);
    static std::map <std::string, std::vector<double>> getTempsByYear(const std::vector<TemperatureRow>& rows,
        unsigned int countryIndex);
    static std::map <std::string, std::vector<double>> getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
        unsigned int countryIndex, const std::string monthDay);
    
    static const std::map<std::string, int> years;
    static const std::map<std::string, unsigned int> countries;

private:
    std::string timestamp;
    std::vector<double> temperatures;

    std::string getYear() const;
    std::string getMonth() const;
    std::string getDay() const;
};

