// Ensure this header file is included only once
#pragma once

// standard library includes
#include <string>
#include <map>
#include <vector>


// create the Temperature class specification
class TemperatureRow
{
// declare the constructor using const as the values do not need to be altered 
// use call by reference so that copies 
public:
    TemperatureRow(const std::string& _utcTimestamp,const std::map<std::string, double>& _countryTemperatures);

    /*std::string getUtcTimestamp() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    double getTemperature(const std::string& countryCode) const;*/

    void printRow() const;

private:
    std::string utcTimestamp;
    std::map<std::string, double> countryTemperatures; // Maps country codes to temperature values
};

