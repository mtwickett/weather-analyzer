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
	CsvReader(); // declare the constructor

	static std::filesystem::path getFilePath();
	static std::vector<TemperatureRow> readcsv(std::filesystem::path filePath);
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);

private:
	static TemperatureRow stringsToTempRow(std::vector<std::string> rowTokens, std::vector<std::string> headers);
};

