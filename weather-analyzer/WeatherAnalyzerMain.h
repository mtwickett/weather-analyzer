#pragma once

#include <iostream>
#include <map>
#include <vector>


#include "TemperatureRow.h"
#include "csvReader.h"

    

class WeatherAnalyzerMain
{
public:
    WeatherAnalyzerMain();

    void init();

private:
    void about();
    void getTemperature();
    void printMenu();
    std::string processOption();

    std::map<std::string, void(WeatherAnalyzerMain::*)()> OPTIONS;
    std::vector<TemperatureRow> rows;
};

