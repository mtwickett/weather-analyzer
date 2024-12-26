#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "TemperatureRow.h"
#include "csvReader.h"
#include "Candlestick.h"

    

class WeatherAnalyzerMain
{
public:
    WeatherAnalyzerMain();
    void init();

private:
    void about();
    void getTemperature();
    void printCandlestickData();
    void plotCandlestickChart();
    void printLineGraphData();
    void plotLineGraph();
    void printMenu();

    std::string processOption();

    std::vector<Candlestick> getCandlestickData();
    std::string getUserCountry();
    std::string getUserPeriodFilter();
    std::string getUserYear();
    std::string getUserMonth();
    std::string getUserDay();
    std::string getUserHour();

    std::map<std::string, void(WeatherAnalyzerMain::*)()> OPTIONS;
    std::vector<TemperatureRow> rows;
    std::string option;
};

