#include "Statistics.h"

// standard library includes
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream>


std::vector<Candlestick> Statistics::calculateCandlesticks(const std::map<std::string, 
	std::vector<double>>& yearToTempsMap)
{
	// Initialize an empty vector to store the resulting candlesticks.
	std::vector<Candlestick> candlesticks;
	
	// If the input map is empty, return an empty candlestick vector.
	if (yearToTempsMap.empty()) {
		return candlesticks;
	}

	// Handle the first year's data where the open will be the same as the close
	const auto& firstYear = *yearToTempsMap.begin(); // Get the first key-value pair in the map.
	const std::string& year = firstYear.first; // Extract the year (key) as a string.
	const std::vector<double>& firstTemps = firstYear.second; // Extract the vector of temperatures

	// Calculate the mean, high, and low temperatures for the first year.
	std::vector<double> meanHighLow = getMeanHighLow(firstTemps);
	double open = meanHighLow[0]; // current year's mean
	double close = meanHighLow[0]; // current year's mean
	double high = meanHighLow[1];
	double low = meanHighLow[2];

	// Create the first Candlestick object and add it to the vector.
	Candlestick candlestick(year, open, close, high, low);
	candlesticks.push_back(candlestick);

	// Iterate from the second element
	for (auto it = std::next(yearToTempsMap.begin()); it != yearToTempsMap.end(); ++it) {
		const std::string& year = it->first; // Extract the year (key) as a string.
		const std::vector<double>& temps = it->second; // Extract the vector of temperatures
		// Calculate the mean, high, and low temperatures
		meanHighLow = getMeanHighLow(temps);
		open = close; // previous years close
		close = meanHighLow[0]; // current year's mean
		high = meanHighLow[1];
		low = meanHighLow[2];

		// Create a Candlestick object and add it to the candlesticks vector
		Candlestick candlestick(year, open, close, high, low);
		candlesticks.push_back(candlestick);
	}
	
	return candlesticks;
}


std::vector<ScatterPlotHighLow> Statistics::calculateScatterPlotHighLows(const std::map<std::string,
	std::vector<double>>& yearToTempsMap)
{
	// Initialize an empty vector to store scatter plot data points.
	std::vector<ScatterPlotHighLow> scatterPlot;

	// If the input map is empty, return the empty scatter plot vector.
	if (yearToTempsMap.empty()) {
		return scatterPlot;
	}

	// Iterate through each entry in the map.
	for (const auto& pair : yearToTempsMap) {
		const std::string& year = pair.first; // Extract the year (key) as a string.
		const std::vector<double>& temps = pair.second; // Extract the vector of temperatures
		// Calculate the high and low temperatures
		std::pair<double, double> highLow = getHighLow(temps);
		double high = highLow.first;
		double low = highLow.second;

		// Create a ScatterPlotHighLow object and add it to the ScatterPlot vector
		ScatterPlotHighLow ScatterPlotHighLow(year, high, low);
		scatterPlot.push_back(ScatterPlotHighLow);
	}

	return scatterPlot;
;
}



/////////////// Private methods //////////////////

std::vector<double> Statistics::getMeanHighLow(const std::vector<double>& temps)
{
	// Check if the input vector is empty. If so, return a default vector of zeros.
	if (temps.empty()) {
		return { 0.0, 0.0, 0.0 };
	}

	// Initialize variables to calculate the sum, high, and low values.
	double sum = 0.0;               // To accumulate the total sum of temperatures.
	double high = temps[0];         // Set the initial high value to the first temperature.
	double low = temps[0];          // Set the initial low value to the first temperature.

	// Loop through each temperature in the vector.
	for (double t : temps) {
		sum += t; // Add the current temperature to the sum.
		if (t > high) // Update the high value if the current temperature is greater.
			high = t; 
		if (t < low) // Update the low value if the current temperature is smaller.
			low = t;
	}

	// Return a vector containing the mean, high, and low values.
	return { sum / temps.size(), high, low };
}


std::pair<double, double> Statistics::getHighLow(const std::vector<double>& temps)
{
	// Check if the input vector is empty. If so, return a default pair of zeros.
	if (temps.empty()) {
		return { 0.0, 0.0 };
	}

	// Initialize variables to calculate the high and low values.
	double high = temps[0];         // Set the initial high value to the first temperature.
	double low = temps[0];          // Set the initial low value to the first temperature.

	// Loop through each temperature in the vector.
	for (double t : temps) {
		if (t > high) // Update the high value if the current temperature is greater.
			high = t;
		if (t < low) // Update the low value if the current temperature is smaller.
			low = t;
	}

	// Return a pair containing the high and low values.
	return { high, low };
}



double Statistics::getCorrelationCoefficient(std::vector<std::pair<std::string, double>> predictionData)
{
	// Check if the input data is empty and throw an exception if it is.
	if (predictionData.empty()) {
		throw std::invalid_argument("Prediction data cannot be empty.");
	}

	// Initialize variables to compute the sums for the correlation formula.
	double sumX = 0.0, sumY = 0.0, sumXY = 0.0;
	double sumXSquared = 0.0, sumYSquared = 0.0;
	// Iterate through each pair in the input vector - 
	// Pair.first: year or day (x-value)
	// Pair.second: temperature (y-value)
	for (const auto& pair : predictionData) {
		double X = std::stod(pair.first);
		double Y = pair.second;
		// Accumulate the sums needed for the correlation coefficient formula.
		sumX += X;                        // Sum of X values.
		sumY += Y;                        // Sum of Y values.
		sumXY += X * Y;                   // Sum of the product of X and Y values.
		sumXSquared += pow(X, 2);         // Sum of squared X values.
		sumYSquared += pow(Y, 2);         // Sum of squared Y values.
	}

	// Number of data points in the input vector.
	size_t numDataPoints = predictionData.size();
	// Calculate the Pearson correlation coefficient (r) using the formula.
	double r = (numDataPoints * sumXY - sumX * sumY) /
		sqrt((numDataPoints * sumXSquared - pow(sumX, 2)) * 
			(numDataPoints * sumYSquared - pow(sumY, 2)));
	
	return r;
}


double Statistics::getLinearRegressionPrediction(std::vector<std::pair<std::string, double>> predictionData,
	double year)
{
	// Check if the input data is empty and throw an exception if it is.
	if (predictionData.empty()) {
		throw std::invalid_argument("Prediction data cannot be empty.");
	}

	// Initialize variables to compute the necessary sums for simple linear regression.
	double sumX = 0.0, sumY = 0.0, sumXY = 0.0;
	double sumXSquared = 0.0;
	// Iterate through each pair in the input vector - 
	// Pair.first: year or day (x-value)
	// Pair.second: temperature (y-value)
	for (const auto& pair : predictionData) {
		double X = std::stod(pair.first);
		double Y = pair.second;
		// Accumulate sums needed for slope and intercept calculations.
		sumX += X;                        // Sum of all X values.
		sumY += Y;                        // Sum of all Y values.
		sumXY += X * Y;                   // Sum of the product of X and Y.
		sumXSquared += pow(X, 2);         // Sum of squared X values.
	}

	// Number of data points in the input vector.
	size_t numDataPoints = predictionData.size();

	// Compute the numerator and denominator for the slope (m) of the regression line.
	double mNumerator = (numDataPoints * sumXY - sumX * sumY);
	double mDenominator = numDataPoints * sumXSquared - pow(sumX, 2);
	// Check for a zero denominator, which indicates the inability to calculate a regression line.
	if (mDenominator == 0.0) {
		throw std::runtime_error("Cannot calculate linear regression");
	}
	// Calculate the slope (m) of the regression line.
	double m = mNumerator / mDenominator;
	// Calculate the y-intercept (b) of the regression line.
	double b = (sumY - m * sumX) / numDataPoints;

	// Predict the dependent variable (Y) for the given independent variable (year).
	return m * year + b;
}


