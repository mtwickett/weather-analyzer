#pragma once

#include <string>


class Candlestick
{

public:
	Candlestick(std::string _year, double _open, double _close, double _high, double _low);

	std::string year;
	double open;
	double close;
	double high;
	double low;

};

