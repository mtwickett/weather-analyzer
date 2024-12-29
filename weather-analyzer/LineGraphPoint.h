#pragma once

#include <string>
#include <map>


class LineGraphPoint
{
public:
	LineGraphPoint(std::string _year, double _high, double _low);

	std::string year;
	double high;
	double low;
};

