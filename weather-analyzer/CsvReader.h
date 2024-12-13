#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include "TemperatureRow.h"


class CsvReader
{
public:
	CsvReader();

	static std::filesystem::path getFilePath();
	static std::vector<TemperatureRow> readcsv(std::filesystem::path filePath);
	static std::vector<std::string> tokenize(std::string csvLine, char delimiter);
};

