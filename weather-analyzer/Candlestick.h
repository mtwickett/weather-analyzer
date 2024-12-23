#pragma once

#include <string>
#include <map>


class Candlestick
{

public:
	Candlestick(std::string _year, double _open, double _close, double _high, double _low);

	std::string year;
	double open;
	double close;
	double high;
	double low;

	static const std::map<std::string, unsigned int> years;

};

