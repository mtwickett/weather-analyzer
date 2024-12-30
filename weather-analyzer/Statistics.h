#pragma once

#include "Candlestick.h"
#include "LineGraphPoint.h"

#include <vector>
#include <map>
#include <string>



class Statistics
{

public:
	static std::vector<Candlestick> calculateCandlesticks(const std::map<std::string, 
		std::vector<double>>& yearToTempsMap);
	static std::vector<LineGraphPoint> calculateLineGraphPoints(const std::map<std::string,
		std::vector<double>>& yearToTempsMap);
	static std::map<int, std::string, std::greater<int>> getCandlestickChart(
		const std::vector<Candlestick>& candlesticks);
	static std::map<int, std::string, std::greater<int>> calculateLineGraphHighs(
		const std::vector<LineGraphPoint>& linegraphPoints);
	static std::map<int, std::string, std::greater<int>> calculateLineGraphLows(
		const std::vector<LineGraphPoint>& linegraphPoints);
	static std::map<int, std::string, std::greater<int>> getHighLowDifferenceScatterPlot(
		const std::vector<LineGraphPoint>& linegraphPoints);

private:
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
	static std::pair<double, double> getHighLow(const std::vector<double>& temps);
	static double getHighLowDifference(std::pair<double, double> highLow);
	static std::map<int, std::string, std::greater<int>> calculateYAxis(const std::vector<Candlestick>& candlesticks);
	static std::map<int, std::string, std::greater<int>> calculateYAxisHighs(const std::vector<LineGraphPoint>& lineGraphPoints);
	static std::map<int, std::string, std::greater<int>> calculateYAxisLows(const std::vector<LineGraphPoint>& lineGraphPoints);
	static std::map<int, std::string, std::greater<int>> calculateYAxisHighLowDiff(const std::vector<LineGraphPoint>& lineGraphPoints)
};

