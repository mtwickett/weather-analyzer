// Ensure this header file is included only once
#pragma once

// standard library includes
#include <string>
#include <map>
#include <vector>


class Candlestick
{
public:
	Candlestick(std::string _year, double _open, double _close, double _high, double _low);

	// Getters for each member
	const std::string& getYear() const;
	double getOpen() const;
	double getClose() const;
	double getHigh() const;
	double getLow() const;

	// Static function that generates a candlestick chart.
	// It takes a vector of Candlestick objects and returns a map where:
	// - The key is the y axis 
	// - The value is a string line at that height on the y axis
	static std::map<int, std::string, std::greater<int>> getCandlestickChart(
		const std::vector<Candlestick>& candlesticks);

private:
	// Helper function that calculates the Y-axis values for the candlestick chart.
	// Returns a map where:
	// - The key is the y axis 
	// - The value is an empty string
	static std::map<int, std::string, std::greater<int>> calculateYAxis(const std::vector<Candlestick>& candlesticks);
	const std::string year;
	double open;
	double close;
	double high;
	double low;
};

