#include "TemperatureRow.h"


TemperatureRow::TemperatureRow(const std::string& _utcTimestamp, const std::map<std::string, double>& _countryTemperatures)
    : utcTimestamp(_utcTimestamp),
      countryTemperatures(_countryTemperatures)
{

}
