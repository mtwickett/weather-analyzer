#pragma once

#include "TemperatureRow.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>


class CsvReader
{
public:
	CsvReader();

	static std::filesystem::path getFilePath();
	static std::vector<TemperatureRow> readcsv(std::filesystem::path filePath);
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);

private:
	static TemperatureRow stringsToTempRow(std::vector<std::string> rowTokens, std::vector<std::string> headers);
};

