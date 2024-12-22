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


std::vector<int> Statistics::calculateYAxisScale(const std::vector<Candlestick>& candlesticks)
{
	// calculate y-axis scale
	std::vector<int> yAxis;
	double yAxisMax = 0.0;
	double yAxisMin = 0.0;
	for (const auto& c : candlesticks) {
		if (c.high > yAxisMax)
			yAxisMax = c.high;
		if (c.low < yAxisMin)
			yAxisMin = c.low;
	}

	int yAxisMaxScaled = static_cast<int>(std::round(yAxisMax / 2.0));
	int yAxisMinScaled = static_cast<int>(std::round(yAxisMin / 2.0));


	if (yAxisMinScaled % 2 == 0 && yAxisMaxScaled % 2 == 1 ||
		yAxisMinScaled % 2 == 1 && yAxisMaxScaled % 2 == 0) {
		yAxisMaxScaled += 1;
	}

	for (int i = yAxisMinScaled; i <= yAxisMaxScaled; i += 2)
		yAxis.push_back(i);

	std::reverse(yAxis.begin(), yAxis.end());

	return yAxis;
}


std::vector<Candlestick> Statistics::calculateCandlesticks(const std::map<std::string, 
	std::vector<double>>& yearToTempsMap)
{
	std::vector<Candlestick> candlesticks;
	
	if (yearToTempsMap.empty()) {
		return candlesticks;
	}

	const auto& year1980 = *yearToTempsMap.begin();
	const std::string& year = year1980.first;
	const std::vector<double>& temps1980 = year1980.second;

	std::vector<double> meanHighLow = getMeanHighLow(temps1980);
	double open = meanHighLow[0];
	double close = meanHighLow[0];
	double high = meanHighLow[1];
	double low = meanHighLow[2];

	Candlestick candlestick(year, open, close, high, low);
	candlesticks.push_back(candlestick);

	for (auto it = std::next(yearToTempsMap.begin()); it != yearToTempsMap.end(); ++it) {
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


std::vector<std::vector<std::string>> Statistics::getChartData(const std::vector<Candlestick>& candlesticks)
{
	std::vector<std::vector<std::string>> chartData;

	std::vector<int> yAxis = calculateYAxisScale(candlesticks);

	for (const auto& y : yAxis) {
		std::cout << y << std::endl;
	}



	return chartData;
}
