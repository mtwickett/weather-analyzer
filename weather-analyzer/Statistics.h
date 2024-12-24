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
	static std::map<int, std::string, std::greater<int>> getYearlyChartData(
		const std::vector<Candlestick>& candlesticks,
		const int& yearStart,
		const int& yearRange);

private:
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
	static std::map<int, std::string, std::greater<int>> calculateYAxisScale(const std::vector<Candlestick>& candlesticks);
};

