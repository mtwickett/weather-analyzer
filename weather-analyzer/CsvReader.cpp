#include "CsvReader.h"


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


const std::vector<TemperatureRow> CsvReader::readcsv(const std::string fileName)
{

	std::vector<TemperatureRow> rows;
	const std::filesystem::path filePath = getFilePath(fileName);
	// pass std::filesystem::path to the ifstream constructor - uses implicit conversion to std::string 
	std::ifstream csvFile{ filePath };
	std::string line;

	if (csvFile.is_open()) {
		// ignore the header line
		std::getline(csvFile, line);

		// get the rest of the rows
		// add each row as type TemperatureRow to the rows vector
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
	std::cout << "The dataset was successfully read in with " << rows.size() << " rows." << std::endl;
	std::cout << "Check the About section for dataset information." << std::endl;

	return rows;
}



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
	
	if (rowTokens.size() != 29) {
		std::cerr << "Error: Line has " << rowTokens.size() << " tokens\n";
		throw std::runtime_error("Invalid number of tokens");
	}
	
	utcTimestamp = rowTokens[0];

	std::vector<std::string> stringTemps(rowTokens.begin() + 1, rowTokens.end());
	for (const auto& t : stringTemps) {
		temps.push_back(std::stod(t));
	}

	TemperatureRow temperatureRow {
		utcTimestamp,
		temps
	};

	return temperatureRow;
}
