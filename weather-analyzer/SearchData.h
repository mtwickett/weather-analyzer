#pragma once

#include "TemperatureRow.h"


class SearchData
{
	SearchData();

public:
	static int getRowIndex(const std::vector<TemperatureRow>& rows,
		const std::string& timestamp);
};

