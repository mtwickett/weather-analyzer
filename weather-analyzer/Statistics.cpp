#include "Statistics.h"

#include <numeric>
#include <algorithm>



std::vector<double> Statistics::getMeanHighLow(const std::vector<double>& temps)
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


std::vector<Candlestick> Statistics::calculateCandlesticks(const std::map<std::string, 
	std::vector<double>>& yearToTempsMap)
{
	std::vector<Candlestick> candlesticks;
	std::vector<double> MeanHighLow;
	std::string year;
	double open;
	double close;
	double high;
	double low;

	for (const auto& pair : yearToTempsMap) {
		MeanHighLow = getMeanHighLow(pair.second);
		year = pair.first;
		if (year == "1980")
			open = pair.second[0];
		else
			open = close;
		close = MeanHighLow[0];
		high = MeanHighLow[1];
		low = MeanHighLow[2];

		Candlestick candlestick(year, open, close, high, low);
		candlesticks.push_back(candlestick);
	}

	return candlesticks;
}
