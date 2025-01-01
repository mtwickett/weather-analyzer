// Ensure this header file is included only once
#pragma once

// standard library includes
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

// project header
#include "TemperatureRow.h"


// create the CsvReader class specification
class CsvReader
{
public:
	// opens and reads the csv file, calls the tokenize() and stringsToTempRow() 
	// methods to return a vector of class type TemperatureRow
	static const std::vector<TemperatureRow> readcsv(const std::string fileName);

private:
	static const std::filesystem::path getFilePath(const std::string fileName); // gets the csv/txt file path 
	// the tokenize function used in the Merkel currency exchange app
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);
	// converts the tokenized file line and file headers to a TemperatureRow
	static TemperatureRow stringsToTempRow(std::vector<std::string> rowTokens);
};

