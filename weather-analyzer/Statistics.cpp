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


std::vector<ScatterPlotHighLow> Statistics::calculateScatterPlotHighLows(const std::map<std::string,
	std::vector<double>>& yearToTempsMap)
{
	std::vector<ScatterPlotHighLow> scatterPlot;

	if (yearToTempsMap.empty()) {
		return scatterPlot;
	}

	for (const auto& pair : yearToTempsMap) {
		const std::string& year = pair.first;
		const std::vector<double>& temps = pair.second;
		std::pair<double, double> highLow = getHighLow(temps);
		double high = highLow.first;
		double low = highLow.second;

		ScatterPlotHighLow lineGraphPoint(year, high, low);
		scatterPlot.push_back(lineGraphPoint);
	}

	return scatterPlot;
;
}


std::map<int, std::string, std::greater<int>> Statistics::getCandlestickChart(
	const std::vector<Candlestick>& candlesticks)
{
	std::map<int, std::string, std::greater<int>> chart = calculateYAxis(candlesticks);
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	for (const auto& c : candlesticks) {
		int open = static_cast<int>(std::round(c.getOpen()));
		int close = static_cast<int>(std::round(c.getClose()));
		int high = static_cast<int>(std::round(c.getHigh()));
		int low = static_cast<int>(std::round(c.getLow()));
		
		
		
		for (auto& pair : chart) {
			if (pair.first >= std::min(open, close) && pair.first <= std::max(open, close)) {
				if (close >= open)
					chart[pair.first] += green + " \u2588" + " " + reset;
				else
					chart[pair.first] += red + " \u2588" + " " + reset;
			}
			else if (pair.first >= low && pair.first <= high) {
				if (close >= open)
					chart[pair.first] += green + " \u2502" + " " + reset;
				else
					chart[pair.first] += red + " \u2502" + " " + reset;
			}
			else {
				chart[pair.first] += "   ";
			}
		}
	}
	return chart;
}


std::map<int, std::string, std::greater<int>> Statistics::calculateScatterPlotHighs(
	const std::vector<ScatterPlotHighLow>& scatterPlot)
{
	std::map<int, std::string, std::greater<int>> lineGraph = calculateYAxisHighs(scatterPlot);
	const std::string reset = "\033[0m";
	const std::string green = "\033[32m";
	;
	
	for (const auto& p : scatterPlot) {
		int high = static_cast<int>(std::round(p.getHigh()));

		for (auto& pair : lineGraph) {
			if (pair.first == high)
				pair.second += green + "+" + "  " + reset;
			else
				pair.second += "\033[38;5;250m\u2591  ";
		}
		
	}
	return lineGraph;
}


std::map<int, std::string, std::greater<int>> Statistics::calculateScatterPlotLows(
	const std::vector<ScatterPlotHighLow>& scatterPlot)
{
	std::map<int, std::string, std::greater<int>> lineGraph = calculateYAxisLows(scatterPlot);
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	
	for (const auto& p : scatterPlot) {
		int low = static_cast<int>(std::round(p.getLow()));

		for (auto& pair : lineGraph) {
			if (pair.first == low)
				pair.second += red + "+" + "  " + reset;
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
		double highest = std::max({ c.getOpen(), c.getClose(), c.getHigh() });
		double lowest = std::min({ c.getOpen(), c.getClose(), c.getLow() });
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


std::map<int, std::string, std::greater<int>> Statistics::calculateYAxisHighs(const std::vector<ScatterPlotHighLow>& scatterPlot)
{
	// calculate y-axis scale
	std::map<int, std::string, std::greater<int>> yAxis;
	double yAxisMax = scatterPlot[0].getHigh();
	double yAxisMin = scatterPlot[0].getHigh();

	for (const auto& p : scatterPlot) {
		if (p.getHigh() > yAxisMax)
			yAxisMax = p.getHigh();
		if (p.getHigh() < yAxisMin)
			yAxisMin = p.getHigh();
	}
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}


std::map<int, std::string, std::greater<int>> Statistics::calculateYAxisLows(const std::vector<ScatterPlotHighLow>& scatterPlot)
{
	// calculate y-axis scale
	std::map<int, std::string, std::greater<int>> yAxis;
	double yAxisMax = scatterPlot[0].getLow();
	double yAxisMin = scatterPlot[0].getLow();

	for (const auto& p : scatterPlot) {
		if (p.getLow() > yAxisMax)
			yAxisMax = p.getLow();
		if (p.getLow() < yAxisMin)
			yAxisMin = p.getLow();
	}
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}


double Statistics::getCorrelationCoefficient(std::vector<std::pair<std::string, double>> predictionData)
{
	if (predictionData.empty()) return 0.0;

	double sumX = 0.0, sumY = 0.0, sumXY = 0.0;
	double sumXSquared = 0.0, sumYSquared = 0.0;
	for (const auto& pair : predictionData) {
		double X = std::stod(pair.first);
		double Y = pair.second;
		sumX += X;
		sumY += Y;
		sumXY += X * Y;
		sumXSquared += pow(X, 2);
		sumYSquared += pow(Y, 2);
	}

	double numDataPoints = predictionData.size();
	double r = (numDataPoints * sumXY - sumX * sumY) /
		sqrt((numDataPoints * sumXSquared - pow(sumX, 2)) * 
			(numDataPoints * sumYSquared - pow(sumY, 2)));
	
	return r;
}


double Statistics::getLinearRegressionPrediction(std::vector<std::pair<std::string, double>> predictionData,
	double year)
{
	if (predictionData.empty()) {
		throw std::invalid_argument("Prediction data cannot be empty.");
	}

	double sumX = 0.0, sumY = 0.0, sumXY = 0.0;
	double sumXSquared = 0.0;
	for (const auto& pair : predictionData) {
		double X = std::stod(pair.first);
		double Y = pair.second;
		sumX += X;
		sumY += Y;
		sumXY += X * Y;
		sumXSquared += pow(X, 2);
	}

	double numDataPoints = predictionData.size();
	double mNumerator = (numDataPoints * sumXY - sumX * sumY);
	double mDenominator = numDataPoints * sumXSquared - pow(sumX, 2);
	if (mDenominator == 0.0) {
		throw std::runtime_error("Cannot calculate linear regression");
	}
	double m = mNumerator / mDenominator;
	double b = (sumY - m * sumX) / numDataPoints;

	return m * year + b;
}


