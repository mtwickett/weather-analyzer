#include "Statistics.h"

#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>


std::vector<Candlestick> Statistics::calculateCandlesticks(const std::map<std::string, 
	std::vector<double>>& yearToTempsMap)
{
	std::vector<Candlestick> candlesticks;
	
	if (yearToTempsMap.empty()) {
		return candlesticks;
	}

	const auto& firstYear = *yearToTempsMap.begin();
	const std::string& year = firstYear.first;
	const std::vector<double>& firstTemps = firstYear.second;

	std::vector<double> meanHighLow = getMeanHighLow(firstTemps);
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


std::vector<LineGraphPoint> Statistics::calculateLineGraphPoints(const std::map<std::string,
	std::vector<double>>& yearToTempsMap)
{
	std::vector<LineGraphPoint> lineGraphPoints;

	if (yearToTempsMap.empty()) {
		return lineGraphPoints;
	}

	for (const auto& pair : yearToTempsMap) {
		const std::string& year = pair.first;
		const std::vector<double>& temps = pair.second;
		std::pair<double, double> highLow = getHighLow(temps);
		double high = highLow.first;
		double low = highLow.second;

		LineGraphPoint lineGraphPoint(year, high, low);
		lineGraphPoints.push_back(lineGraphPoint);
	}

	return lineGraphPoints;
}


std::map<int, std::string, std::greater<int>> Statistics::getCandlestickChart(
	const std::vector<Candlestick>& candlesticks)
{
	std::map<int, std::string, std::greater<int>> chart = calculateYAxis(candlesticks);
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	
	for (const auto& c : candlesticks) {
		int open = static_cast<int>(std::round(c.open));
		int close = static_cast<int>(std::round(c.close));
		int high = static_cast<int>(std::round(c.high));
		int low = static_cast<int>(std::round(c.low));
		
		
		
		for (auto& pair : chart) {
			if (pair.first >= std::min(open, close) && pair.first <= std::max(open, close)) {
				if (close >= open)
					chart[pair.first] += " " + green + "==" + reset;
				else
					chart[pair.first] += " " + red + "==" + reset;
			}
			else if (pair.first >= low && pair.first <= high) {
				if (close >= open)
					chart[pair.first] += " " + green + "||" + reset;
				else
					chart[pair.first] += " " + red + "||" + reset;
			}
			else {
				chart[pair.first] += "   ";
			}
		}
	}
	return chart;
}


std::map<int, std::string, std::greater<int>> Statistics::calculateLineGraph(
	const std::vector<LineGraphPoint>& linegraphPoints)
{
	std::map<int, std::string, std::greater<int>> lineGraph = calculateYAxis(linegraphPoints);
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	for (const auto& p : linegraphPoints) {
		int high = static_cast<int>(std::round(p.high));
		int low = static_cast<int>(std::round(p.low));

		for (auto& pair : lineGraph) {
			if (pair.first == high && pair.first == low)
				pair.second += " ++";
			else if (pair.first == high)
				pair.second += " " + green + "++" + reset;
			else if (pair.first == low)
				pair.second += " " + red + "++" + reset;
			else
				pair.second += "   ";
		}
	}
	return lineGraph;

}


/////////////// Private methods //////////////////

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


std::pair<double, double> Statistics::getHighLow(const std::vector<double>& temps)
{
	if (temps.empty()) {
		return { 0.0, 0.0 };
	}

	double high = temps[0];
	double low = temps[0];

	for (double t : temps) {
		if (t > high)
			high = t;
		if (t < low)
			low = t;
	}

	return { high, low };
}



std::map<int, std::string, std::greater<int>> Statistics::calculateYAxis(const std::vector<Candlestick>& candlesticks)
{
	// calculate y-axis scale
	std::map<int, std::string, std::greater<int>> yAxis;
	double yAxisMax = std::numeric_limits<double>::min();
	double yAxisMin = std::numeric_limits<double>::max();

	for (const auto& c : candlesticks) {
		double highest = std::max({ c.open, c.close, c.high });
		double lowest = std::min({ c.open, c.close, c.low });
		if (highest > yAxisMax)
			yAxisMax = highest;
		if (lowest < yAxisMin)
			yAxisMin = lowest;
	}
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));


	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}


std::map<int, std::string, std::greater<int>> Statistics::calculateYAxis(const std::vector<LineGraphPoint>& lineGraphPoints)
{
	// calculate y-axis scale
	std::map<int, std::string, std::greater<int>> yAxis;
	double yAxisMax = std::numeric_limits<double>::min();
	double yAxisMin = std::numeric_limits<double>::max();

	for (const auto& p : lineGraphPoints) {
		if (p.high > yAxisMax)
			yAxisMax = p.high;
		if (p.low < yAxisMin)
			yAxisMin = p.low;
	}
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}
