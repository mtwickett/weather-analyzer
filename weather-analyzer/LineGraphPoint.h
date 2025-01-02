#pragma once

#include <string>
#include <map>


class LineGraphPoint
{
public:
	LineGraphPoint(std::string _year, double _high, double _low);

	const std::string& getYear() const;
	double getHigh() const;
	double getLow() const;

private:
	const std::string year;
	double high;
	double low;
};

