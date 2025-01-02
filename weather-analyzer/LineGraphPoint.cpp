#include "LineGraphPoint.h"


LineGraphPoint::LineGraphPoint(std::string _year, double _high, double _low)
	: year(_year), high(_high), low(_low)
{

}


const std::string& LineGraphPoint::getYear() const {
	return year;
}


double LineGraphPoint::getHigh() const {
	return high;
}

double LineGraphPoint::getLow() const {
	return low;
}