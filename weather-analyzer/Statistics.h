#pragma once

#include <vector>

class Statistics
{
public:
	static double getAverage(std::vector<double> temps);
	static double getHigh(std::vector<double> temps);
	static double getLow(std::vector<double> temps);


};

