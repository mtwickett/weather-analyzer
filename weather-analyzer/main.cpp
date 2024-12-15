#include "CsvReader.h"
#include "TemperatureRow.h"


int main()
{
	std::vector<TemperatureRow> rows = CsvReader::readcsv(CsvReader::getFilePath());
	rows[0].printRow();
}