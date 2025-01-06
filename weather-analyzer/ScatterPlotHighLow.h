#pragma once

#include <string>
#include <map>
#include <vector>


class ScatterPlotHighLow
{
public:
	ScatterPlotHighLow(std::string _year, double _high, double _low);

	// Member getters
	const std::string& getYear() const;
	double getHigh() const;
	double getLow() const;

	// Static method: Calculates the scatter plot data for highs.
	// Takes a vector of ScatterPlotHighLow objects and maps the Y-axis values to their graphical representation.
	static std::map<int, std::string, std::greater<int>> calculateScatterPlotHighs(
		const std::vector<ScatterPlotHighLow>& scatterPlotHighLows);
	// Static method: Calculates the scatter plot data for lows.
	// Takes a vector of ScatterPlotHighLow objects and maps the Y-axis values to their graphical representation.
	static std::map<int, std::string, std::greater<int>> calculateScatterPlotLows(
		const std::vector<ScatterPlotHighLow>& scatterPlotHighLows);

private:
	const std::string year;
	double high;
	double low;

	// Static helper method: Calculates the Y-axis values for high points in the scatter plot.
	// Returns a map where:
	// - The key is the y axis 
	// - The value is an empty string
	static std::map<int, std::string, std::greater<int>> calculateYAxisHighs(const std::vector<ScatterPlotHighLow>& scatterPlotHighLows);
	// Static helper method: Calculates the Y-axis values for low points in the scatter plot.
	// Returns a map where:
	// - The key is the y axis 
	// - The value is an empty string
	static std::map<int, std::string, std::greater<int>> calculateYAxisLows(const std::vector<ScatterPlotHighLow>& scatterPlotHighLows);
};

