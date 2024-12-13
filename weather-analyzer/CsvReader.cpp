#include "CsvReader.h"



std::filesystem::path CsvReader::getFilePath()
{
	std::filesystem::path rootPath = std::filesystem::current_path();
	std::filesystem::path filePath = rootPath / "data" / "utc_timestamp,AT_temperature,BE_tem.txt";

	try {
		if (!std::filesystem::exists(filePath))
		{
			throw std::runtime_error("Error: Path does not exist: " + filePath.string());
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return filePath;
}


std::vector<TemperatureRow> CsvReader::readcsv(std::filesystem::path filePath)
{
	std::vector<TemperatureRow> rows;
	// pass std::filesystem::path to the ifstream constructor - uses implicit conversion to std::string 
	std::ifstream csvFile{ filePath };
	std::string line;

	if (csvFile.is_open()) {
		while (std::getline(csvFile, line)) {
			try {
				TemperatureRow tempRow = stringsToTempRow(tokenize(line, ','));
				rows.push_back(tempRow);
			}
			catch (const std::exception e) {
				std::cout << "Bad line" << std::endl;
			}
		}
	}
	std::cout << "csvReader::readcsv read " << rows.size() << " rows" << std::endl;

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
		tokens.push_back(token);
		start = end + 1;
	} while (end != std::string::npos);

	return tokens;
}


TemperatureRow CsvReader::stringsToTempRow(std::vector<std::string> tokens)
{
	double price, amount;
	std::string timestamp, product;
	OrderBookType orderBookType;

	if (tokens.size() != 5) {
		std::cout << "Line has " << tokens.size() << " tokens" << std::endl;
		throw std::exception{};
	}

	try {
		price = std::stod(tokens[3]);
		amount = std::stod(tokens[4]);
	}
	catch (const std::exception& e) {
		std::cout << "Bad double" << std::endl;
		throw e;
	}

	timestamp = tokens[0];
	product = tokens[1];
	orderBookType = OrderBookEntry::stringToOrderBookType(tokens[2]);

	OrderBookEntry orderBookEntry{
		price,
		amount,
		timestamp,
		product,
		orderBookType
	};

	return orderBookEntry;
}
