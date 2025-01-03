#include "ScatterPlotHighLow.h"


ScatterPlotHighLow::ScatterPlotHighLow(std::string _year, double _high, double _low)
	: year(_year), high(_high), low(_low)
{

}


const std::string& ScatterPlotHighLow::getYear() const {
	return year;
}


double ScatterPlotHighLow::getHigh() const {
	return high;
}

double ScatterPlotHighLow::getLow() const {
	return low;
}