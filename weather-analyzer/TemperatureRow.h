#pragma once

#include <string>
#include <map>
#include <vector>


class TemperatureRow
{

private:
    std::string utcTimestamp;
    std::map<std::string, double> countryTemperatures; // Maps country codes to temperature values

public:
    TemperatureRow(const std::string& _utcTimestamp, const std::map<std::string, double>& _countryTemperatures);

    std::string getUtcTimestamp() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    double getTemperature(const std::string& countryCode) const;

    void printRow() const;
};

