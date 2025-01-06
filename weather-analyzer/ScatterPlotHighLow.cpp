#include "ScatterPlotHighLow.h"

#include <cmath>


ScatterPlotHighLow::ScatterPlotHighLow(std::string _year, double _high, double _low)
	: year(_year), high(_high), low(_low)
{

}


const std::string& ScatterPlotHighLow::getYear() const {
	return year;
}


double ScatterPlotHighLow::getHigh() const {
	return high;
}

double ScatterPlotHighLow::getLow() const {
	return low;
}



std::map<int, std::string, std::greater<int>> ScatterPlotHighLow::calculateScatterPlotHighs(
	const std::vector<ScatterPlotHighLow>& scatterPlotHighLows)
{
	// Calculate the Y-axis scale for the candlestick chart.
	// The Y-axis values are stored in a map ordered in descending order (std::greater<int>).
	std::map<int, std::string, std::greater<int>> scatterPlot = calculateYAxisHighs(scatterPlotHighLows);

	// ANSI escape codes for color formatting (green for high points).
	const std::string reset = "\033[0m";
	const std::string green = "\033[32m";
	
	// Iterate over the vector of ScatterPlotHighLow objects.
	for (const auto& p : scatterPlotHighLows) {
		// Round the high value to the nearest integer for plotting.
		int high = static_cast<int>(std::round(p.getHigh()));

		// Iterate over the scatter plot map.
		for (auto& pair : scatterPlot) {
			// If the current Y-axis level matches the high value, add a green "+" symbol.
			if (pair.first == high)
				pair.second += green + "+" + "  " + reset;
			// Else add 3 empty spaces to fill the space to the next year
			else
				pair.second += "   ";
		}

	}
	return scatterPlot;
}


std::map<int, std::string, std::greater<int>> ScatterPlotHighLow::calculateScatterPlotLows(
	const std::vector<ScatterPlotHighLow>& scatterPlotHighLows)
{
	// Calculate the Y-axis scale for the candlestick chart.
	// The Y-axis values are stored in a map ordered in descending order (std::greater<int>).
	std::map<int, std::string, std::greater<int>> scatterPlot = calculateYAxisLows(scatterPlotHighLows);
	// ANSI escape codes for color formatting (red for low points).
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";

	// Iterate over the vector of ScatterPlotHighLow objects.
	for (const auto& p : scatterPlotHighLows) {
		int low = static_cast<int>(std::round(p.getLow()));
		// Iterate over the scatter plot map.
		for (auto& pair : scatterPlot) {
			// If the current Y-axis level matches the low value, add a red "+" symbol.
			if (pair.first == low)
				pair.second += red + "+" + "  " + reset;
			// Else add 3 empty spaces to fill the space to the next year
			else
				pair.second += "   ";
		}
	}
	return scatterPlot;
}


std::map<int, std::string, std::greater<int>> ScatterPlotHighLow::calculateYAxisHighs(const std::vector<ScatterPlotHighLow>& scatterPlotHighLows)
{
	// calculate y-axis scale
	// The Y-axis values are stored in a map ordered in descending order (std::greater<int>).
	std::map<int, std::string, std::greater<int>> yAxis;

	// Start the min and max high values with the first high value
	double yAxisMax = scatterPlotHighLows[0].getHigh();
	double yAxisMin = scatterPlotHighLows[0].getHigh();

	// Iterate over the vector of ScatterPlotHighLow objects.
	for (const auto& p : scatterPlotHighLows) {
		// Update the maximum and minimum Y-axis values if necessary.
		if (p.getHigh() > yAxisMax)
			yAxisMax = p.getHigh();
		if (p.getHigh() < yAxisMin)
			yAxisMin = p.getHigh();
	}
	// Round the maximum and minimum Y-axis values to the nearest integers to scale the y-axis
	// and allow data points to be rounded and assigned to a key in the map 
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	// Insert the map keys from the max high to the min high and assign an empty string as each value.
	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}


std::map<int, std::string, std::greater<int>> ScatterPlotHighLow::calculateYAxisLows(const std::vector<ScatterPlotHighLow>& scatterPlotHighLows)
{
	// calculate y-axis scale
	// The Y-axis values are stored in a map ordered in descending order (std::greater<int>).
	std::map<int, std::string, std::greater<int>> yAxis;
	// Start the min and max high values with the first low value
	double yAxisMax = scatterPlotHighLows[0].getLow();
	double yAxisMin = scatterPlotHighLows[0].getLow();

	// Iterate over the vector of ScatterPlotHighLow objects.
	for (const auto& p : scatterPlotHighLows) {
		// Update the maximum and minimum Y-axis values if necessary.
		if (p.getLow() > yAxisMax)
			yAxisMax = p.getLow();
		if (p.getLow() < yAxisMin)
			yAxisMin = p.getLow();
	}
	// Round the maximum and minimum Y-axis values to the nearest integers to scale the y-axis
	// and allow data points to be rounded and assigned to a key in the map.
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	// Insert the map keys from the max low to the min low and assign an empty string as each value.
	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}
