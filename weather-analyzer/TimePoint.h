#pragma once

#include <string>
#include <map>
#include <vector>


class TimePoint
{
private:
    std::string utcTimestamp;
    std::map<std::string, double> temperatures; // Maps country codes to temperature values

public:
    TimePoint(const std::string& line_, const std::vector<std::string>& headers_);
};

