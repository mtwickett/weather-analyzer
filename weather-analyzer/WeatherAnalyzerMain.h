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
    void instructions();
    void getExchangeStats();
    void makeAnAsk();
    void makeABid();
    void getWallet();
    void getNextTimeFrame();
    void printMenu();
    std::string processOption();

    std::map<std::string, void(WeatherAnalyzerMain::*)()> OPTIONS;
    OrderBook orderBook{ "test.csv" };
};

