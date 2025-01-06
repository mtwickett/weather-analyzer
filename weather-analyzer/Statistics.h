// Ensure this header file is included only once
#pragma once

// standard library includes
#include <vector>
#include <map>
#include <string>
// project headers
#include "Candlestick.h"
#include "ScatterPlotHighLow.h"

class Statistics
{

public:
	// Calculates candlesticks (open, close, high, low) for each year from a given map of year-to-temperatures.
	// Input: A map where keys are years (strings) and values are vectors of temperatures (doubles).
	// Output: A vector of Candlestick objects, each representing a year's temperature statistics.
	static std::vector<Candlestick> calculateCandlesticks(const std::map<std::string, 
		std::vector<double>>& yearToTempsMap);
	// Calculates scatter plot data for high and low temperatures over years.
	// Input: A map where keys are years (strings) and values are vectors of temperatures (doubles).
	// Output: A vector of ScatterPlotHighLow objects, each representing high and low values for a year.
	static std::vector<ScatterPlotHighLow> calculateScatterPlotHighLows(const std::map<std::string,
		std::vector<double>>& yearToTempsMap);
	// Calculates the correlation coefficient for a given set of data points.
	// Input: A vector of pairs, where each pair contains a year (string) and a value (double).
	// Output: A double representing the correlation coefficient, indicating the strength and direction of the relationship.
	static double getCorrelationCoefficient(std::vector<std::pair<std::string, double>> predictionData);
	// Predicts a temperature with simple linear regression using the least squares method.
	// Input: A vector of pairs (year as string, value as double) representing historical data and a year (double) for prediction.
	// Output: A double representing the predicted temperature for the provided data.
	static double getLinearRegressionPrediction(std::vector<std::pair<std::string, double>> predictionData, double year);
	// Calculates the mean, high, and low temperatures from a vector of temperatures.
	// Input: A vector of temperatures (doubles).
	// Output: A vector containing three doubles: the mean, high, and low temperatures.
	static std::vector<double> getMeanHighLow(const std::vector<double>& temps);
	// Finds the highest and lowest temperatures from a given set of temperatures.
	// Input: A vector of temperatures (doubles).
	// Output: A pair of doubles representing the highest and lowest temperatures.
	static std::pair<double, double> getHighLow(const std::vector<double>& temps);
};

