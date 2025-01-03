#pragma once

#include "Candlestick.h"
#include "ScatterPlotHighLow.h"

#include <vector>
#include <map>
#include <string>



class Statistics
{

public:
	static std::vector<Candlestick> calculateCandlesticks(const std::map<std::string, 
		std::vector<double>>& yearToTempsMap);
	static std::vector<ScatterPlotHighLow> calculateScatterPlotHighLows(const std::map<std::string,
		std::vector<double>>& yearToTempsMap);
	static std::map<int, std::string, std::greater<int>> getCandlestickChart(
		const std::vector<Candlestick>& candlesticks);
	static std::map<int, std::string, std::greater<int>> calculateScatterPlotHighs(
		const std::vector<ScatterPlotHighLow>& scatterPlot);
	static std::map<int, std::string, std::greater<int>> calculateScatterPlotLows(
		const std::vector<ScatterPlotHighLow>& ScatterPlot);
	static double getCorrelationCoefficient(std::vector<std::pair<std::string, double>> predictionData);
	static double getLinearRegressionPrediction(std::vector<std::pair<std::string, double>> predictionData, double year);

private:
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
	static std::pair<double, double> getHighLow(const std::vector<double>& temps);
	static std::map<int, std::string, std::greater<int>> calculateYAxis(const std::vector<Candlestick>& candlesticks);
	static std::map<int, std::string, std::greater<int>> calculateYAxisHighs(const std::vector<ScatterPlotHighLow>& scatterPlot);
	static std::map<int, std::string, std::greater<int>> calculateYAxisLows(const std::vector<ScatterPlotHighLow>& scatterPlot);
	
};

