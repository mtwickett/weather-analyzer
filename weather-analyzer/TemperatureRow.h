#pragma once

#include <string>
#include <map>
#include <vector>


class TemperatureRow
{

private:
    std::string utcTimestamp;
    std::map<std::string, double> temperatures; // Maps country codes to temperature values

public:
    TemperatureRow(const std::string& _line, const std::vector<std::string>& _headers);

    std::string getUtcTimestamp() const;
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    double getTemperature(const std::string& countryCode) const;

    void printRow() const;
};

