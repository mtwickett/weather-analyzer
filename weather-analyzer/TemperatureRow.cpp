#include "TemperatureRow.h"

#include <iostream>


TemperatureRow::TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures)
    : timestamp(_timestamp),
      temperatures(_temperatures)
{

}

const std::map<std::string, unsigned int> TemperatureRow::countries = {
    {"Austria", 0},
    {"Belgium", 1},
    {"Bulgaria", 2},
    {"Switzerland", 3},
    {"Czech_republic", 4},
    {"Germany", 5},
    {"Denmark", 6},
    {"Estonia", 7},
    {"Spain", 8},
    {"Finland", 9},
    {"France", 10},
    {"United_kingdom", 11},
    {"Greece", 12},
    {"Croatia", 13},
    {"Hungary", 14},
    {"Ireland", 15},
    {"Italy", 16},
    {"Lithuania", 17},
    {"Luxembourg", 18},
    {"Latvia", 19},
    {"Netherlands", 20},
    {"Norway", 21},
    {"Poland", 22},
    {"Portugal", 23},
    {"Romania", 24},
    {"Sweden", 25},
    {"Slovenia", 26},
    {"Slovakia", 27}
};

// Getter for timestamp
std::string TemperatureRow::getTimestamp() const {
    return timestamp;
}

// Parse year from UTC timestamp
int TemperatureRow::getYear() const {
    return std::stoi(timestamp.substr(0, 4)); // "1980-01-01T00:00:00Z"
}

// Parse month from UTC timestamp
int TemperatureRow::getMonth() const {
    return std::stoi(timestamp.substr(5, 2));
}

// Parse day from UTC timestamp
int TemperatureRow::getDay() const {
    return std::stoi(timestamp.substr(8, 2));
}

int TemperatureRow::getHour() const {
    return std::stoi(timestamp.substr(11, 13));
}


void TemperatureRow::printRow() {
    std::cout << "UTC Timestamp: " << timestamp << "\n";
    for (const auto& pair : countries) {
        std::cout << pair.first << ": " << temperatures[pair.second] << std::endl;
    }
}

