// Ensure this header file is included only once
#pragma once

// standard library includes
#include <string>
#include <map>
#include <vector>


enum Headers {
    AUSTRIA,
    BELGIUM,
    BULGARIA,
    SWITZERLAND,
    CZECH_REPUBLIC,
    GERMANY,
    DENMARK,
    ESTONIA,
    SPAIN,
    FINLAND,
    FRANCE,
    UNITED_KINGDOM,
    GREECE,
    CROATIA,
    HUNGARY,
    IRELAND,
    ITALY,
    LITHUANIA,
    LUXEMBOURG,
    LATVIA,
    NETHERLANDS,
    NORWAY,
    POLAND,
    PORTUGAL,
    ROMANIA,
    SWEDEN,
    SLOVENIA,
    SLOVAKIA
};


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

private:
    std::vector<std::string> countries = {
        "Austria",
        "Belgium",
        "Bulgaria",
        "Switzerland",
        "Czech_republic",
        "Germany",
        "Denmark",
        "Estonia",
        "Spain",
        "Finland",
        "France",
        "United_kingdom",
        "Greece",
        "Croatia",
        "Hungary",
        "Ireland",
        "Italy",
        "Lithuania",
        "Luxembourg",
        "Latvia",
        "Netherlands",
        "Norway",
        "Poland",
        "Portugal",
        "Romania",
        "Sweden",
        "Slovenia",
        "Slovakia"
    };

};

