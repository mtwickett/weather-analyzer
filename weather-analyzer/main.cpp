#include "CsvReader.h"


int main()
{
	std::vector<TemperatureRow> rows = CsvReader::readcsv(CsvReader::getFilePath());
	std::cout << rows[0] << std::endl;
	return 0;
}