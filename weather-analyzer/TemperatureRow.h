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
    TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures);
    
    std::string getTimestamp() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;

    void printRow();

    std::string timestamp;
    std::vector<double> temperatures;


    static const std::map<std::string, unsigned int> countries;
};

