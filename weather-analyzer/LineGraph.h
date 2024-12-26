#pragma once

#include <string>
#include <map>


class LineGraph
{
public:
	LineGraph(std::string _year, double _high, double _low);

	std::string year;
	double high;
	double low;
};

