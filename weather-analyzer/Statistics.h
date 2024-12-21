#pragma once

#include "Candlestick.h"

#include <vector>
#include <map>
#include <string>

class Statistics
{
public:
	static double getAverage(std::vector<double> temps);
	static double getHigh(std::vector<double> temps);
	static double getLow(std::vector<double> temps);
	static std::vector<Candlestick> calculateCandlesticks(std::map<std::string, 
		std::vector<double>> yearToTempsMap);
};

