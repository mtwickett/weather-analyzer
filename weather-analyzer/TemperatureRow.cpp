#include "TemperatureRow.h"

#include <cmath>


TemperatureRow::TemperatureRow(const std::string& _timestamp, const std::vector<double>& _temperatures)
    : timestamp(_timestamp),
      temperatures(_temperatures)
{

}

const std::vector<double>& TemperatureRow::getTemperatures() const
{
	return TemperatureRow::temperatures;
}


const int TemperatureRow::getRowIndex(const std::vector<TemperatureRow>& rows,
	const std::string& searchTimestamp)
{
	int left = 0, right = int(rows.size() - 1);

	while (left <= right) {
		int mid = int(floor((left + right) / 2));
		std::string tsMid = rows[mid].timestamp;

		if (searchTimestamp == tsMid)
			return mid;

		if (searchTimestamp < tsMid)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}


std::map <std::string, std::vector<double>> TemperatureRow::getTempsByYear(const std::vector<TemperatureRow>& rows,
	unsigned int countryIndex)
{
	std::map<std::string, std::vector<double>> yearTemps;
	std::string currentYear = rows[0].getYear();
	std::vector<double> temps;


	for (const auto& row : rows) {
		if (currentYear == row.getYear()) {
			temps.push_back(row.temperatures[countryIndex]);
		}
		else {
			yearTemps[currentYear] = temps;
			currentYear = row.getYear();
			temps.clear();
			temps.push_back(row.temperatures[countryIndex]);
		}
	}
	yearTemps[currentYear] = temps;

	return yearTemps;
}


std::map <std::string, std::vector<double>> TemperatureRow::getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
	unsigned int countryIndex, const std::string monthDay)
{
	std::map<std::string, std::vector<double>> dayOfYearTemps;
	std::string currentYear = rows[0].getYear();
	std::vector<double> temps;

	for (const auto& row : rows) {
		if (currentYear == row.getYear()) {
			if (row.getMonth() + "-" + row.getDay() == monthDay) {
				temps.push_back(row.temperatures[countryIndex]);
			}
		}
		else {
			dayOfYearTemps[currentYear] = temps;
			currentYear = row.getYear();
			temps.clear();
			if (row.getMonth() + "-" + row.getDay() == monthDay) {
				temps.push_back(row.temperatures[countryIndex]);
			}
		}
	}

	dayOfYearTemps[currentYear] = temps;

	return dayOfYearTemps;
}


const std::map<std::string, int> TemperatureRow::years = {
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


// Parse year from UTC timestamp
std::string TemperatureRow::getYear() const {
    return timestamp.substr(0, 4); // "1980-01-01T00:00:00Z"
}

std::string TemperatureRow::getMonth() const {
    return timestamp.substr(5, 2); // "1980-01-01T00:00:00Z"
}

// Parse day from UTC timestamp
std::string TemperatureRow::getDay() const {
    return timestamp.substr(8, 2);
}

