#pragma once

#include "TemperatureRow.h"
#include "csvReader.h"
#include "Candlestick.h"
#include "LineGraphPoint.h"

    

class WeatherAnalyzerMain
{
public:
    WeatherAnalyzerMain();
    void init();

private:
    void about();
    void getTemperature();
    void printCandlestickData();
    void plotCandlestickChart(std::vector<Candlestick> candlesticks);
    void plotCandlestickChart();
    void printLineGraphData();
    void plotLineGraph();
    void getPredictionDayTemp();
    void printMenu();

    std::string processOption();
    std::vector<Candlestick> getCandlestickData();
    std::vector<LineGraphPoint> getLineGraphData();
    std::string getUserCountry();
    std::string getUserPeriodFilter();
    std::string getUserCandlestickOption();
    std::pair<std::string, std::string> getUserYearRange();
    std::string getUserHighLow();
    std::string getUserYear();
    std::string getUserMonth();
    std::string getUserDay();
    std::string getUserHour();
    double getUserPredictionYear();

    std::map<std::string, void(WeatherAnalyzerMain::*)()> OPTIONS;
    std::vector<TemperatureRow> rows;
    std::string option;
};

