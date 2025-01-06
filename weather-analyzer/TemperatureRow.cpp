// Related header
#include "TemperatureRow.h"

// standard library includes
#include <cmath>


TemperatureRow::TemperatureRow(std::string _timestamp, std::vector<double> _temperatures)
    : timestamp(std::move(_timestamp)),   // Move timestamp into the member
	  temperatures(std::move(_temperatures)) // Move temperatures into the member
{

}


const std::vector<double>& TemperatureRow::getTemperatures() const
{
	return TemperatureRow::temperatures;
}

// Uses binary search to locate a timestamp in a vector of temperature rows sorted by timestamp. 
const int TemperatureRow::getRowIndex(const std::vector<TemperatureRow>& rows,
	const std::string& searchTimestamp)
{
	// Initialize pointers to the left most and right most indices
	int left = 0, right = int(rows.size() - 1);

	// Continue searching while the left pointer is still less than or equal to the right pointer.
	while (left <= right) {

		// Get the middle index and element.
		int mid = int(floor((left + right) / 2));
		std::string tsMid = rows[mid].timestamp;

		// Return row index if found.
		if (searchTimestamp == tsMid)
			return mid;
		// If the search timestamp is less than the midpoint timestamp, adjust the search range
		// to exclude the right half.
		if (searchTimestamp < tsMid)
			right = mid - 1;
		// If the search timestamp is greater than the midpoint timestamp, adjust the search range
		// to exclude the left half.
		else
			left = mid + 1;
	}

	// Return -1 if not found.
	return -1;
}


// Groups temperature data by year from a vector of TemperatureRow objects.
// For each year, it creates a mapping of the year (as a string) to a vector of temperatures 
// for the specified country index.
std::map <std::string, std::vector<double>> TemperatureRow::getTempsByYear(const std::vector<TemperatureRow>& rows,
	unsigned int& countryIndex)
{
	// Initialize the map to store year-to-temperatures mapping.
	std::map<std::string, std::vector<double>> yearTemps;
	// Start with the year of the first row and an empty vector of temperatures.
	std::string currentYear = rows[0].getYear();
	std::vector<double> temps;

	// Iterate over each TemperatureRow in the rows vector.
	for (const auto& row : rows) {
		// Check the current year still matches the row year and add the row temperature for the chosen country.
		if (currentYear == row.getYear()) {
			temps.push_back(row.temperatures[countryIndex]);
		}
		// The row year has moved to the next year and does not match the current year.
		// Map the current year to a vector of temperatures from that year for the chosen country.
		// Update the current year, empty the vector and add the current row as the first temperature
		// for the next year.
		else {
			yearTemps[currentYear] = temps;
			currentYear = row.getYear();
			temps.clear();
			temps.push_back(row.temperatures[countryIndex]);
		}
	}
	// Add the final years temps to the map (2019)
	yearTemps[currentYear] = temps;

	return yearTemps;
}


// Groups temperature data by a day of the year from a vector of TemperatureRow objects.
// For each year, it creates a mapping of the year (as a string) to a vector of temperatures 
// for the specified country index. 
std::map <std::string, std::vector<double>> TemperatureRow::getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
	unsigned int& countryIndex, const std::string& monthDay)
{
	// Initialize the map to store year-to-temperatures mapping.
	std::map<std::string, std::vector<double>> dayOfYearTemps;
	// Start with the year of the first row and an empty vector of temperatures.
	std::string currentYear = rows[0].getYear();
	std::vector<double> temps;

	// Iterate over each TemperatureRow in the rows vector.
	for (const auto& row : rows) {
		// Check the current year still matches the row year.
		if (currentYear == row.getYear()) {
			// Check the month and day matches the chosen day and add the row temperature for the chosen country.
			if (row.getMonth() + "-" + row.getDay() == monthDay) {
				temps.push_back(row.temperatures[countryIndex]);
			}
		}
		// The row year has moved to the next year and does not match the current year.
		// Map the current year to a vector of temperatures from that day of the year for the chosen country.
		// Update the current year and empty the vector.
		else {
			dayOfYearTemps[currentYear] = temps;
			currentYear = row.getYear();
			temps.clear();
			// If the first row of the next year matches the month and day (this woulod be January 1st at 00:00),
			// add this row to the empty vector
			if (row.getMonth() + "-" + row.getDay() == monthDay) {
				temps.push_back(row.temperatures[countryIndex]);
			}
		}
	}

	// Add the final years temps to the map (2019)
	dayOfYearTemps[currentYear] = temps;

	return dayOfYearTemps;
}


const std::map<std::string, unsigned int> TemperatureRow::years = {
	{"1980", 0},
	{"1981", 1},
	{"1982", 2},
	{"1983", 3},
	{"1984", 4},
	{"1985", 5},
	{"1986", 6},
	{"1987", 7},
	{"1988", 8},
	{"1989", 9},
	{"1990", 10},
	{"1991", 11},
	{"1992", 12},
	{"1993", 13},
	{"1994", 14},
	{"1995", 15},
	{"1996", 16},
	{"1997", 17},
	{"1998", 18},
	{"1999", 19},
	{"2000", 20},
	{"2001", 21},
	{"2002", 22},
	{"2003", 23},
	{"2004", 24},
	{"2005", 25},
	{"2006", 26},
	{"2007", 27},
	{"2008", 28},
	{"2009", 29},
	{"2010", 30},
	{"2011", 31},
	{"2012", 32},
	{"2013", 33},
	{"2014", 34},
	{"2015", 35},
	{"2016", 36},
	{"2017", 37},
	{"2018", 38},
	{"2019", 39}
};


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


///////////////// Private methods ///////////////////


// Extracts and returns the year component from the timestamp string.
std::string TemperatureRow::getYear() const {
	// Extracts the first 4 characters representing the year.
    return timestamp.substr(0, 4); 
}

// Extracts and returns the month component from the timestamp string.
std::string TemperatureRow::getMonth() const {
	// Extracts the characters at positions 5 and 6, representing the month.
    return timestamp.substr(5, 2); 
}


// Extracts and returns the day component from the timestamp string.
std::string TemperatureRow::getDay() const {
	// Extracts the characters at positions 8 and 9, representing the day.
    return timestamp.substr(8, 2);
}

