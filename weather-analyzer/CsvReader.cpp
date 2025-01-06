#include "CsvReader.h"

// standard library includes
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>

// project header
#include "TemperatureRow.h"

// Opens and reads the csv file, calls the tokenize() and stringsToTempRow() 
// methods and returns a vector of class type TemperatureRow
const std::vector<TemperatureRow> CsvReader::readcsv(const std::string fileName)
{

	std::vector<TemperatureRow> rows;
	// create a path to the csv file using the getFilePath method
	const std::filesystem::path filePath = getFilePath(fileName);
	// pass std::filesystem::path to the ifstream constructor - uses implicit conversion to std::string 
	std::ifstream csvFile{ filePath };
	std::string line;

	if (csvFile.is_open()) {
		// ignore the header line
		std::getline(csvFile, line);

		// get the rest of the rows
		// add each row as type TemperatureRow to the "rows" vector
		while (std::getline(csvFile, line)) {
			try {
				TemperatureRow row = stringsToTempRow(tokenize(line, ','));
				rows.push_back(row);
			}
			catch (const std::exception e) {
				std::cout << "Bad line" << std::endl;
			}
		}
	}
	// Print the amount of rows read in.
	std::cout << "The dataset was successfully read in with " << rows.size() << " rows." << std::endl;
	std::cout << "Check the About section for dataset information." << std::endl;

	return rows;
}


// Wrote this function myself, it builds a path to the csv file from the root path
// Returns the file path if the file exists
const std::filesystem::path CsvReader::getFilePath(const std::string fileName)
{
	std::filesystem::path rootPath = std::filesystem::current_path();
	std::filesystem::path filePath = rootPath / "data" / fileName;

	if (!std::filesystem::exists(filePath))
	{
		throw std::runtime_error("Path does not exist: " + filePath.string());
	}

	return filePath;
}


// Added a line to remove any whitespace including \n \t \r in each token
std::vector<std::string> CsvReader::tokenize(std::string csvLine, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	signed int start, end;
	start = csvLine.find_first_not_of(delimiter, 0);

	do {
		end = csvLine.find_first_of(delimiter, start);
		if (start == csvLine.length() || start == end) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);
		// Added a removal of any whitewpace
		token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
		tokens.push_back(token);
		start = end + 1;
	} while (end != std::string::npos);

	return tokens;
}



TemperatureRow CsvReader::stringsToTempRow(std::vector<std::string> rowTokens)
{
	std::string utcTimestamp;
	std::vector<double> temps;
	
	// The row must have 29 tokens
	if (rowTokens.size() != 29) {
		std::cerr << "Error: Line has " << rowTokens.size() << " tokens\n";
		throw std::runtime_error("Invalid number of tokens");
	}
	
	// Move the first token (timestamp) from the rowTokens to avoid copying
	utcTimestamp = std::move(rowTokens[0]);

	// Extract the remaining tokens (temperature values) into stringTemps
	std::vector<std::string> stringTemps(rowTokens.begin() + 1, rowTokens.end());
	for (const auto& t : stringTemps) {
		try
		{
			temps.push_back(std::stod(t));
		}
		catch (const std::exception& e)
		{
			std::cout << "Bad double" << std::endl;
			throw e;
		}
	}

	// Create a TemperatureRow object, move both the timestamp and the temperatures to avoid copying
	TemperatureRow temperatureRow {
		std::move(utcTimestamp),
		std::move(temps)
	};

	return temperatureRow;
}
