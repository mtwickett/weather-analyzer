// Ensure this header file is included only once
#pragma once

// standard library includes
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

// project header
#include "TemperatureRow.h"


// create the CsvReader class specification
class CsvReader
{
public:
	// declaring the constructor CsvReader(); is not necessary because all 
	// the methods are static and do not require an instance of the class 
	
	static std::filesystem::path getFilePath(const std::string fileName); // gets the csv/txt file path 

	// opens and reads the csv file, calls the tokenize() and stringsToTempRow() 
	// methods to return a vector of class type TemperatureRow
	static std::vector<TemperatureRow> readcsv(const std::filesystem::path filePath);

	// the tokenize function used in the Merkel currency exchange app
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);

private:
	// converts the tokenized file line and file headers to a TemperatureRow
	static TemperatureRow stringsToTempRow(std::vector<std::string> rowTokens);
};

