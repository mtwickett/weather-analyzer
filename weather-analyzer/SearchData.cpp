#include "SearchData.h"

#include <cmath>


int SearchData::getRowIndex(const std::vector<TemperatureRow>& rows, 
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


std::vector<TemperatureRow> SearchData::getRowsByYear(const std::vector<TemperatureRow>& rows,
	const std::string& year)
{
	std::vector<TemperatureRow> rowsByYear;
	for (const auto& row : rows) {
		std::string rowYear = row.getYear();
		if (rowYear == year)
			rowsByYear.push_back(row);
		else if (rowYear > year)
			break;
	}
	return rowsByYear;
}


std::vector<TemperatureRow> SearchData::getRowsByMonth(const std::vector<TemperatureRow>& rows,
	const std::string& month)
{
	std::vector<TemperatureRow> rowsByMonth;
	for (const auto& row : rows) {
		std::string rowMonth = row.getMonth();
		if (rowMonth == month)
			rowsByMonth.push_back(row);
		else if (rowMonth > month)
			break;
	}
	return rowsByMonth;
}


std::map <std::string, std::vector<double>> getTempsByYear(const std::vector<TemperatureRow>& rows,
	unsigned int countryIndex)
{
	std::map<std::string, std::vector<double>> yearTemps;
	std::string currentYear = rows[0].getYear();
	std::vector<double> temps;


	for (const auto& row : rows) {
		if (currentYear == row.getYear())
			temps.push_back(row.temperatures)
	}

}
