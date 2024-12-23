#include "Statistics.h"

#include <numeric>
#include <algorithm>
#include <cmath>

#include <iostream>



std::vector<double> Statistics::getMeanHighLow(const std::vector<double>& temps)
{
	if (temps.empty()) {
		return { 0.0, 0.0, 0.0 };
	}

	double sum = 0.0;
	double high = temps[0];
	double low = temps[0];

	for (double t : temps) {
		sum += t;
		if (t > high)
			high = t;
		if (t < low)
			low = t;
	}

	return { sum / temps.size(), high, low };
}


std::map<int, std::string, std::greater<int>> Statistics::calculateYAxisScale(const std::vector<Candlestick>& candlesticks)
{
	// calculate y-axis scale
	std::map<int, std::string, std::greater<int>> yAxis;
	double yAxisMax = 0.0;
	double yAxisMin = 0.0;
	for (const auto& c : candlesticks) {
		if (c.high > yAxisMax)
			yAxisMax = c.high;
		if (c.low < yAxisMin)
			yAxisMin = c.low;
	}

	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));


	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}


std::vector<Candlestick> Statistics::calculateCandlesticks(const std::map<std::string, 
	std::vector<double>>& dateToTempsMap)
{
	std::vector<Candlestick> candlesticks;
	
	if (dateToTempsMap.empty()) {
		return candlesticks;
	}

	const auto& firstYear = *dateToTempsMap.begin();
	const std::string& year = firstYear.first;
	const std::vector<double>& firstTemps = firstYear.second;

	std::vector<double> meanHighLow = getMeanHighLow(firstTemps);
	double open = meanHighLow[0];
	double close = meanHighLow[0];
	double high = meanHighLow[1];
	double low = meanHighLow[2];

	Candlestick candlestick(year, open, close, high, low);
	candlesticks.push_back(candlestick);

	for (auto it = std::next(dateToTempsMap.begin()); it != dateToTempsMap.end(); ++it) {
		const std::string& year = it->first;
		const std::vector<double>& temps = it->second;
		meanHighLow = getMeanHighLow(temps);
		open = close;
		close = meanHighLow[0];
		high = meanHighLow[1];
		low = meanHighLow[2];

		Candlestick candlestick(year, open, close, high, low);
		candlesticks.push_back(candlestick);
	}
	
	return candlesticks;
}


std::map<int, std::string, std::greater<int>> Statistics::getYearlyChartData(
	const std::vector<Candlestick>& candlesticks,
	const unsigned int& yearStart,
	const unsigned int& yearEnd)
{

	std::map<int, std::string, std::greater<int>> chart = calculateYAxisScale(candlesticks);

	std::vector<Candlestick> yearsSub(candlesticks.begin() + yearStart, candlesticks.begin() + yearEnd);
	for (const auto& c : yearsSub) {
		int open = static_cast<int>(std::round(c.open));
		int close = static_cast<int>(std::round(c.close));
		int high = static_cast<int>(std::round(c.high));
		int low = static_cast<int>(std::round(c.low));


		for (auto& pair : chart) {
			if (pair.first >= low && pair.first <= high) {
				if (pair.first >= std::min(open, close) && pair.first <= std::max(open, close))
					chart[pair.first] += "   ==";
				else 
					chart[pair.first] += "   ||";
			}
		}
		
	}
	return chart;
}
