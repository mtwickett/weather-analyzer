#pragma once

#include "TemperatureRow.h"


class SearchData
{
	SearchData();

public:
	static int getRowIndex(const std::vector<TemperatureRow>& rows,
		const std::string& timestamp);
	std::vector<TemperatureRow> getRowsByYear(const std::vector<TemperatureRow>& rows,
		const std::string& year);
	std::vector<TemperatureRow> getRowsByMonth(const std::vector<TemperatureRow>& rows,
		const std::string& month);
	static std::map <std::string, std::vector<double>> getTempsByYear(const std::vector<TemperatureRow>& rows,
		unsigned int countryIndex);
	static std::map <std::string, std::vector<double>> getTempsByDayOfYear(const std::vector<TemperatureRow>& rows,
		unsigned int countryIndex, std::string day);

};

