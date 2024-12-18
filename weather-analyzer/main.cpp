#include "CsvReader.h"
#include <iostream>


int main()
{
	/*std::cout << CsvReader::getFilePath() << std::endl;*/
	try
	{
		std::vector<TemperatureRow> rows = CsvReader::readcsv(CsvReader::getFilePath("utc_timestamp,AT_temperature,BE_tem.txt"));
		rows[0].printRow();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}