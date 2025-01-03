#pragma once

#include "TemperatureRow.h"
#include "csvReader.h"
#include "Candlestick.h"
#include "ScatterPlotHighLow.h"

    

class WeatherAnalyzerMain
{
public:
    WeatherAnalyzerMain();
    void init();

private:
    std::string country = "";
    std::string period = "";
    std::string month = "";
    std::string day = "";
    const std::string red = "\033[31m";
    const std::string cyan = "\033[36m";
    const std::string reset = "\033[0m";

    void about();
    void getUserInput();
    void getTemperature();
    void printCandlestickData();
    void plotCandlestickChart(std::vector<Candlestick> candlesticks);
    void plotCandlestickChart();
    void printScatterPlotData();
    void plotScatterPlot();
    void getPredictionTemp();
    void printMenu();
    
    std::string processOption();
    std::vector<Candlestick> getCandlestickData();
    std::vector<ScatterPlotHighLow> getScatterPlotData();
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
    std::map<std::string, std::string> months = {
        {"01", "January"}, {"02", "February"}, {"03", "March"}, {"04", "April"},
        {"05", "May"}, {"06", "June"}, {"07", "July"}, {"08", "August"},
        {"09", "September"}, {"10", "October"}, {"11", "November"}, {"12", "December"}
    };
};

