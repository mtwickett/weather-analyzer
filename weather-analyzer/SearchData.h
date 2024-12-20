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

};

