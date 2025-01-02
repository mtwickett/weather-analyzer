#pragma once

#include <string>
#include <map>


class Candlestick
{

public:
	Candlestick(std::string _year, double _open, double _close, double _high, double _low);

	const std::string& getYear() const;
	double getOpen() const;
	double getClose() const;
	double getHigh() const;
	double getLow() const;

private:
	const std::string year;
	double open;
	double close;
	double high;
	double low;
};

