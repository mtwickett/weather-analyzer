#include "Candlestick.h"
#include "Statistics.h"

#include <cmath>


Candlestick::Candlestick(std::string _year, double _open, double _close, double _high, double _low)
    : year(_year), open(_open), close(_close), high(_high), low(_low)
{

}


const std::string& Candlestick::getYear() const {
    return year;
}

double Candlestick::getOpen() const {
    return open;
}

double Candlestick::getClose() const {
    return close;
}

double Candlestick::getHigh() const {
    return high;
}

double Candlestick::getLow() const {
    return low;
}

// Returns a descending map where the key is a rounded Y-axis value and the value is a string 
// line at that y-axis height for each year with a text representation of a candlstick
std::map<int, std::string, std::greater<int>> Candlestick::getCandlestickChart(
	const std::vector<Candlestick>& candlesticks)
{
	// Initialize the chart map with calculated Y-axis values.
	// The map is ordered in descending order to print from the top of the graph to the bottom
	std::map<int, std::string, std::greater<int>> chart = calculateYAxis(candlesticks);
	// Define ANSI color escape codes for terminal output.
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	// Iterate over each candlestick in the input vector and round the open, close, high, and low.
	for (const auto& c : candlesticks) {
		int open = static_cast<int>(std::round(c.getOpen()));
		int close = static_cast<int>(std::round(c.getClose()));
		int high = static_cast<int>(std::round(c.getHigh()));
		int low = static_cast<int>(std::round(c.getLow()));


		// Iterate over each Y-axis level in the chart from top to bottom.
		for (auto& pair : chart) {
			// If the current Y-axis level is within the open-close range, draw a filled block.
			if (pair.first >= std::min(open, close) && pair.first <= std::max(open, close)) {
				if (close >= open)
					chart[pair.first] += green + " \u2588" + " " + reset; // Green block for positive candlestick
				else
					chart[pair.first] += red + " \u2588" + " " + reset; // Red block for positive candlestick
			}
			// Else if the current Y-axis level is within the low-high range, draw a vertical line.
			else if (pair.first >= low && pair.first <= high) {
				if (close >= open)
					chart[pair.first] += green + " \u2502" + " " + reset; // Green block for positive candlestick
				else
					chart[pair.first] += red + " \u2502" + " " + reset; // Red block for positive candlestick
			}
			// Else add 3 empty spaces to fill the space to the next year
			else {
				chart[pair.first] += "   ";
			}
		}
	}
	return chart;
}


// Returns a map with decsending y-axis values as keys and an empty string as values
std::map<int, std::string, std::greater<int>> Candlestick::calculateYAxis(const std::vector<Candlestick>& candlesticks)
{
	// Calculate the Y-axis scale for the candlestick chart.
	// The Y-axis values are stored in a map ordered in descending order (std::greater<int>).
	std::map<int, std::string, std::greater<int>> yAxis;
	// Initialize variables to store the maximum and minimum values of the Y-axis.
	double yAxisMax = std::numeric_limits<double>::min(); // Smallest possible double value.
	double yAxisMin = std::numeric_limits<double>::max(); // Largest possible double value.

	// Iterate through the candlesticks to find the maximum and minimum Y-axis values.
	for (const auto& c : candlesticks) {
		// Find the highest and lowest values among the open, close, high, and low prices.
		double highest = std::max({ c.getOpen(), c.getClose(), c.getHigh() });
		double lowest = std::min({ c.getOpen(), c.getClose(), c.getLow() });
		// Update the maximum and minimum Y-axis values if necessary.
		if (highest > yAxisMax)
			yAxisMax = highest;
		if (lowest < yAxisMin)
			yAxisMin = lowest;
	}

	// Round the maximum and minimum Y-axis values to the nearest integers to scale the y-axis
	// and allow data points to be rounded and assigned to a key in the map 
	int yAxisMaxRound = static_cast<int>(std::round(yAxisMax));
	int yAxisMinRound = static_cast<int>(std::round(yAxisMin));

	// Create the Y-axis map with integer levels from the rounded maximum to minimum values.
	// Each level is initialized with an empty string to hold chart data later.
	for (int i = yAxisMaxRound; i >= yAxisMinRound; i -= 1) {
		yAxis[i] = "";
	}

	return yAxis;
}