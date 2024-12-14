#include "TemperatureRow.h"


TemperatureRow::TemperatureRow(const std::string& _line, const std::vector<std::string>& _headers)
    : utcTimestamp(CsvReader::tokenize(_line, ','))
{

    // Initialize the `temperatures` map using the headers and the line
    for (size_t i = 0; i < headers.size(); ++i) {
        temperatures[headers[i]] = CsvReader::tokenize(line, i);
    }
}
