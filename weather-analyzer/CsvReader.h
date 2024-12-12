#pragma once

#include "TimePoint.h"

#include <vector>


class CsvReader
{
public:
	CsvReader();

	static std::vector<TimePoint> readcsv(std::string csvFile);
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);
};

