#include "TemperatureRow.h"

#include <iostream>


TemperatureRow::TemperatureRow(const std::string& _utcTimestamp, const std::map<std::string, double>& _countryTemperatures)
    : utcTimestamp(_utcTimestamp),
      countryTemperatures(_countryTemperatures)
{

}


void TemperatureRow::printRow() const {
    std::cout << "UTC Timestamp: " << utcTimestamp << "\nTemperatures:\n";
    for (const auto& [country, temp] : countryTemperatures) {
        std::cout << country << ": " << temp << std::endl;
    }
}