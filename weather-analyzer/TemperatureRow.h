// Ensure this header file is included only once
#pragma once

// standard library includes
#include <string>
#include <map>
#include <vector>
#include <iostream>


class TemperatureRow
{
// Declare the constructor with `const` references to avoid copying and ensure the arguments are not modified.
public:
    TemperatureRow(std::string _timestamp, std::vector<double> _temperatures);

    // Getter for the TemperatureRow temperatures
    // Returns a const reference to the temperatures vector to avoid copying while allowing read-only access.
    const std::vector<double>& getTemperatures() const;

    // Finds and returns the index of the row matching the specified timestamp from the vector of rows.
    // Static because it operates on a collection of TemperatureRow objects, not a specific instance.
    static const int getRowIndex(const std::vector<TemperatureRow>& rows, const std::string& timestamp);
    // Groups temperatures by year and returns a map where keys are years (as strings)
    // and values are vectors of temperatures of type double. The `countryIndex` determines which country's data to group.
    static std::map <std::string, std::vector<double>> getTempsByYear(const std::vector<TemperatureRow>& rows,
        unsigned int& countryIndex);
    // Groups temperatures by a day of the year and returns a map where keys are years (as strings)
    // and values are vectors of temperatures of type double. The `countryIndex` determines which country's data to group.
    static std::map <std::string, std::vector<double>> getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
        unsigned int& countryIndex, const std::string& monthDay);
    
    // Static map to associate year strings with integer values, providing a lookup for available years.
    static const std::map<std::string, unsigned int> years;
    // Static map to associate country names (as strings) with unsigned integer indices, 
    // providing a lookup for country-specific data.
    static const std::map<std::string, unsigned int> countries;

private:
    std::string timestamp;
    std::vector<double> temperatures;

    std::string getYear() const;
    std::string getMonth() const;
    std::string getDay() const;
};

