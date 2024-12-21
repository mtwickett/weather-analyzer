#include "Statistics.h"

#include <numeric>
#include <algorithm>


double Statistics::getAverage(std::vector<double> temps)
{
	if (temps.empty()) {
		return 0.0;
	}
	double sum = std::accumulate(temps.begin(), temps.end(), 0.0);
	return sum / temps.size();
}


double Statistics::getHigh(std::vector<double> temps)
{
	if (temps.empty()) {
		return 0.0;
	}
	return *std::max_element(temps.begin(), temps.end());
}


double Statistics::getLow(std::vector<double> temps)
{
	if (temps.empty()) {
		return 0.0;
	}
	return *std::min_element(temps.begin(), temps.end());
}


std::vector<Candlestick> calculateCandlesticks(std::map<std::string, 
	std::vector<double>> yearToTempsMap)
{
	std::string year;
	double open;
	double close;
	double high;
	double low;




}
