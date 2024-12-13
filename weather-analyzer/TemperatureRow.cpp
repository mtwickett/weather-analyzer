#include "TemperatureRow.h"


TemperatureRow::TemperatureRow(const std::string& line, const std::vector<std::string>& headers)
    : utcTimestamp(CsvReader::tokenize(line))  // Initialize `utcTimestamp'
{

    // Initialize the `temperatures` map using the headers and the line
    for (size_t i = 0; i < headers.size(); ++i) {
        temperatures[headers[i]] = CsvReader::tokenize(line, i);
    }
}
