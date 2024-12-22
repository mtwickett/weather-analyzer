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
	static std::vector<std::vector<std::string>> getChartData(const std::vector<Candlestick>& candlesticks);

private:
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
	static std::map<int, std::vector<int>, std::greater<int>> calculateYAxisScale(const std::vector<Candlestick>& candlesticks);
};

