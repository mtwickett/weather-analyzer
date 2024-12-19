#include "TemperatureRow.h"

#include <iostream>


TemperatureRow::TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures)
    : timestamp(_timestamp),
      temperatures(_temperatures)
{

}


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
    for (size_t i = 0; i < temperatures.size(); ++i) {
        std::cout << countries[i] << ": " << temperatures[i] << std::endl;
    }
}

