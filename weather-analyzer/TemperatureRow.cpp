#include "TemperatureRow.h"

#include <iostream>


TemperatureRow::TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures)
    : timestamp(_timestamp),
      temperatures(_temperatures)
{

}

const std::map<std::string, unsigned int> TemperatureRow::countries = {
    {"AUSTRIA", 0},
    {"BELGIUM", 1},
    {"BULGARIA", 2},
    {"SWITZERLAND", 3},
    {"CZECH REPUBLIC", 4},
    {"GERMANY", 5},
    {"DENMARK", 6},
    {"ESTONIA", 7},
    {"SPAIN", 8},
    {"FINLAND", 9},
    {"FRANCE", 10},
    {"UNITED KINGDOM", 11},
    {"GREECE", 12},
    {"CROATIA", 13},
    {"HUNGARY", 14},
    {"IRELAND", 15},
    {"ITALY", 16},
    {"LITHUANIA", 17},
    {"LUXEMBOURG", 18},
    {"LATVIA", 19},
    {"NETHERLANDS", 20},
    {"NORWAY", 21},
    {"POLAND", 22},
    {"PORTUGAL", 23},
    {"ROMANIA", 24},
    {"SWEDEN", 25},
    {"SLOVENIA", 26},
    {"SLOVAKIA", 27}
};

// Getter for timestamp
std::string TemperatureRow::getTimestamp() const {
    return timestamp;
}

// Parse year from UTC timestamp
std::string TemperatureRow::getYear() const {
    return timestamp.substr(0, 4); // "1980-01-01T00:00:00Z"
}

// Parse month from UTC timestamp
std::string TemperatureRow::getMonth() const {
    return timestamp.substr(5, 2);
}

// Parse day from UTC timestamp
std::string TemperatureRow::getDay() const {
    return timestamp.substr(8, 2);
}

std::string TemperatureRow::getHour() const {
    return timestamp.substr(11, 13);
}


void TemperatureRow::printRow() {
    std::cout << "UTC Timestamp: " << timestamp << "\n";
    for (const auto& pair : countries) {
        std::cout << pair.first << ": " << temperatures[pair.second] << std::endl;
    }
}

