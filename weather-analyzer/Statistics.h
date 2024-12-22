#pragma once

#include "Candlestick.h"

#include <vector>
#include <map>
#include <string>


class Statistics
{

public:
	static std::vector<Candlestick> calculateCandlesticks(const std::map<std::string, 
		std::vector<double>>& yearToTempsMap);

private:
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
};

