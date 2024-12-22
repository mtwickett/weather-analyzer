#include "Statistics.h"

#include <numeric>
#include <algorithm>



std::vector<double> getMeanHighLow(const std::vector<double>& temps)
{
	if (temps.empty()) {
		return { 0.0, 0.0, 0.0 };
	}

	double sum = 0.0;
	double high = temps[0];
	double low = temps[0];

	for (double t : temps) {
		sum += t;
		if (t > high)
			high = t;
		if (t < low)
			low = t;
	}

	return { sum / temps.size(), high, low };
}


std::vector<Candlestick> calculateCandlesticks(std::map<std::string, 
	std::vector<double>>& yearToTempsMap)
{
	std::vector<double> MeanHighLow;
	std::string year;
	double open;
	double close;
	double high;
	double low;

	for (const auto& pair : yearToTempsMap) {
		MeanHighLow = Statistics::getMeanHighLow(pair.second);
		year = pair.first;

		high = MeanHighLow[1];
		low = MeanHighLow[2];
	}


}
