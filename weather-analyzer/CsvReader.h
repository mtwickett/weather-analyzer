// Ensure this header file is included only once
#pragma once

// standard library includes
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

// project header
#include "TemperatureRow.h"


class CsvReader
{
public:
	/** Takes a string csv/txt file name as input and returns
	a vector of each row as type TemperatureRow */
	static const std::vector<TemperatureRow> readcsv(const std::string fileName);
private:
	/** Takes a string csv/txt file name as input and returns 
	a path to the file */ 
	static const std::filesystem::path getFilePath(const std::string fileName);
	// the tokenize function used in the Merkel currency exchange app
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);
	/** Takes a vector containing row data points and returns a type TemperatureRow 
	containing a utcTimestamp and a vector of temperatures of type double.
	Excludes the csv file header */
	static TemperatureRow stringsToTempRow(std::vector<std::string> rowTokens);
};

