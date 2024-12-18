#include "TemperatureRow.h"

#include <iostream>


TemperatureRow::TemperatureRow(const std::string _timestamp, const std::vector<double>& _temperatures)
    : timestamp(_timestamp),
      temperatures(_temperatures)
{

}

void TemperatureRow::printRow() {
    std::cout << "UTC Timestamp: " << timestamp << "\n";
    for (size_t i = 0; i < temperatures.size(); ++i) {
        std::cout << countries[i] << ": " << temperatures[i] << std::endl;
    }
}