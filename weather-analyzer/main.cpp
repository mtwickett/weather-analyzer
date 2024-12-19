#include "CsvReader.h"
#include <iostream>


int main()
{
	try
	{
		std::vector<TemperatureRow> rows = CsvReader::readcsv(CsvReader::getFilePath("utc_timestamp,AT_temperature,BE_tem.txt"));
		TemperatureRow firstRow = rows[23];
		firstRow.printRow();
		std::cout << firstRow.getTimestamp() << std::endl;
		std::cout << firstRow.getYear() << std::endl;
		std::cout << firstRow.getMonth() << std::endl;
		std::cout << firstRow.getDay() << std::endl;
		std::cout << firstRow.getHour() << std::endl;

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}