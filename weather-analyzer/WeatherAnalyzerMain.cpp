#include "WeatherAnalyzerMain.h"
#include "Candlestick.h"
#include "Statistics.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>


WeatherAnalyzerMain::WeatherAnalyzerMain()
{
    OPTIONS = {
        {"1", &WeatherAnalyzerMain::about},
        {"2", &WeatherAnalyzerMain::getTemperature},
        {"3", &WeatherAnalyzerMain::printCandlestickData},
        {"4", &WeatherAnalyzerMain::plotCandlestickChart},
        {"5", &WeatherAnalyzerMain::printLineGraphData},
        {"6", &WeatherAnalyzerMain::plotLineGraph}
    };
}


void WeatherAnalyzerMain::init()
{
    try
    {
        rows = CsvReader::readcsv(CsvReader::getFilePath("weather_data_EU_1980-2019_temp_only.csv"));
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    do {
        printMenu();
        WeatherAnalyzerMain::option = processOption();

    } while (WeatherAnalyzerMain::option != "e");
    std::cout << "Exiting options" << std::endl;
}


void WeatherAnalyzerMain::printMenu()
{
    std::vector<std::string> MENU = {
        "\n=======================",
        "Please enter an option 1-6 or press e to exit",
        "=======================",
        "1: About",
        "2: Get a Temperature",
        "3: Print Candlestick Data",
        "4: Plot Candlestick Chart",
        "5: Print Line Graph",
        "6: Plot Line Graph",
        "======================="
    };

    for (const auto& option : MENU) {
        std::cout << option << std::endl;
    }
}


std::string WeatherAnalyzerMain::processOption()
{
    std::string option;
    std::getline(std::cin, option);
    if (OPTIONS.find(option) != OPTIONS.end()) {
        std::cout << "You chose option " << option << ".\n" << std::endl;
        (this->*OPTIONS[option])();
    }
    else if (option != "e") {
        std::cout << "Invalid entry" << std::endl;
    }
    return option;
}


void WeatherAnalyzerMain::about()
{
    std::cout << "---Check weather temperatures in European countries---" << std::endl;
}


void WeatherAnalyzerMain::getTemperature()
{
    std::string country = getUserCountry();
    std::string year = getUserYear();
    std::string month = getUserMonth();
    std::string day = getUserDay();
    std::string hour = getUserHour();

    std::string timestamp = year + "-" + month + "-" + day + "T" + hour + ":00:00Z";
    std::cout << "You chose " << country << " at " << timestamp << std::endl;
  
    try
    {
        double temp;
        int rowIndex = TemperatureRow::getRowIndex(rows, timestamp);
        unsigned int tempIndex = TemperatureRow::countries.at(country);
        temp = rows[rowIndex].temperatures[tempIndex];
        std::cout << "Temperature Degrees Celcius: " << temp << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "No data" << e.what() << std::endl;
    }
}

// get only the data
std::vector<Candlestick> WeatherAnalyzerMain::getCandlestickData()
{
    std::string country = getUserCountry();
    unsigned int countryIndex = TemperatureRow::countries.at(country);
    std::string period = getUserPeriodFilter();

    while (period != "1" && period != "2") {
        std::cout << "Invalid entry" << std::endl;
        period = getUserPeriodFilter();
    }
    
    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<Candlestick> candlesticks;

    
    if (period == "1") {
        std::cout << "You chose Year" << std::endl;
        yearToTempsMap = TemperatureRow::getTempsByYear(rows, countryIndex);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
    }
    else {
        std::cout << "You chose Day" << std::endl;
        std::string month = getUserMonth();
        std::string day = getUserDay();
        std::string monthDay = month + "-" + day;
        yearToTempsMap = TemperatureRow::getTempsByDayOfYear(rows, countryIndex, monthDay);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
    }

    return candlesticks;
}


void WeatherAnalyzerMain::printCandlestickData()
{
    std::vector<Candlestick> candlesticks = getCandlestickData();

    std::cout << "YEAR |  OPEN |  CLOSE |  HIGH  |  LOW" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    for (const auto& c : candlesticks) {
        std::cout << std::fixed << std::setprecision(3) << 
            c.year << " | " << c.open << " | " << c.close <<
            " | " << c.high << " | " <<c.low << std::endl;
    }

    // ask user if they want to plot the candlesticks
    std::string answer = getUserCandlestickOption();

    while (answer != "1" && answer != "2") {
        std::cout << "Invalid entry" << std::endl;
        answer = getUserCandlestickOption();
    }

    if (answer == "1") {
        std::cout << "You chose Yes" << std::endl;
        plotCandlestickChart(candlesticks);
    }
    else {
        std::cout << "You chose No" << std::endl;
    }
        

}


void WeatherAnalyzerMain::plotCandlestickChart(std::vector<Candlestick> candlesticks)
{
    std::map<int, std::string, std::greater<int>> chart = Statistics::getCandlestickChart(candlesticks);
    
    std::cout << std::endl;

    for (const auto& pair : chart) {
        std::cout << std::setw(4)
            << pair.first << "   "
            << pair.second
            << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::string xAxis = "        ";
    for (const auto& pair : TemperatureRow::years) {
        xAxis += pair.first.substr(2, 2) + " ";
    }
    std::cout << "\n" << xAxis << std::endl;
}


void WeatherAnalyzerMain::plotCandlestickChart()
{
    std::string country;
    std::string range;
    std::string filter;
    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Choose a country from the following list:" << std::endl;
    for (const auto& pair : TemperatureRow::countries) {
        std::cout << pair.first << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    std::getline(std::cin, country);

    for (auto& u : country) {
        u = std::toupper(u);
    }

    std::cout << "Choose a year range .eg. 1980-2019 or 1985-1990" << std::endl;
    std::getline(std::cin, range);


    std::string yearStartKey = range.substr(0, 4);
    std::string yearEndKey = range.substr(5, 4);
    int yearStart;
    int yearEnd;
    int yearRange;

    if (TemperatureRow::years.find(yearStartKey) != TemperatureRow::years.end() &&
        TemperatureRow::years.find(yearEndKey) != TemperatureRow::years.end()) {
        yearStart = TemperatureRow::years.at(yearStartKey);
        yearEnd = TemperatureRow::years.at(yearEndKey);
        yearRange = yearEnd - yearStart + 1;
    }
    else {
        std::cerr << "One or both years not found in the map." << std::endl;
    }
    
    std::cout << "You chose: " << country << "\n" << std::endl;
    unsigned int countryIndex = TemperatureRow::countries.at(country);
    // choose by day or year
    std::cout << "Choose filter by year or filter by day" << std::endl;
    std::cout << "For filter by year: Press 1" << std::endl;
    std::cout << "For filter by day: Press 2" << std::endl;
    std::getline(std::cin, filter);

    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<Candlestick> candlesticks;
    std::map<int, std::string, std::greater<int>> chart;
    if (filter == "1") {
        yearToTempsMap = TemperatureRow::getTempsByYear(rows, countryIndex);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
        chart = Statistics::getCandlestickChart(candlesticks);
    }
    else if (filter == "2") {
        std::string day;
        std::cout << "Enter a month and day as: 01-01" << std::endl;
        std::getline(std::cin, day);
        yearToTempsMap = TemperatureRow::getTempsByDayOfYear(rows, countryIndex, day);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
        try
        {
            chart = Statistics::getCandlestickChart(candlesticks);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

    }

    std::cout << "\n" << std::endl;
    for (const auto& pair : chart) {
        std::cout << std::setw(4) << pair.first << "   " << pair.second << std::endl;
    }

    auto itStart = TemperatureRow::years.find(yearStartKey);
    auto itEnd = TemperatureRow::years.find(yearEndKey);
    if (itEnd != TemperatureRow::years.end()) {
        ++itEnd;
    }
    std::string xAxis = "        ";

    for (auto it = itStart; it != itEnd; ++it) {
        xAxis += it->first.substr(2, 2) + " ";
    }
    std::cout << "\n" << xAxis << std::endl;
}


void WeatherAnalyzerMain::printLineGraphData()
{
    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<LineGraph> lineGraph;
    std::map<int, std::string, std::greater<int>> chart;

    // prompt user for a country  
    std::string country = getUserCountry();
    unsigned int countryIndex = TemperatureRow::countries.at(country);

    std::string day;
    std::cout << "Enter a month and day as: 01-01" << std::endl;
    std::getline(std::cin, day);
    
    yearToTempsMap = TemperatureRow::getTempsByDayOfYear(rows, countryIndex, day);


    

}


void WeatherAnalyzerMain::plotLineGraph()
{

}


std::string WeatherAnalyzerMain::getUserCountry()
{
    std::string country;
    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Choose a country from the following selection:" << std::endl;
    for (const auto& pair : TemperatureRow::countries) {
        std::cout << pair.first << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    std::getline(std::cin, country);
    for (auto& u : country) {
        u = std::toupper(u);
    }

    std::cout << "You chose: " << country << std::endl;
    return country;
}


std::string WeatherAnalyzerMain::getUserPeriodFilter()
{
    std::string period;

    std::cout << "---Input instructions---" << std::endl;
    std::cout << "Choose period of data to be Year or Day" << std::endl;
    std::cout << "Please enter an option 1-2" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1: Year" << std::endl;
    std::cout << "2: Day" << std::endl;
    std::cout << "=======================" << std::endl;

    std::getline(std::cin, period);

    return period;
}


std::string WeatherAnalyzerMain::getUserCandlestickOption()
{
    std::string plotCandlesticks;
    std::cout << std::endl;
    std::cout << "Would you like to plot the candlesticks?" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1: Yes" << std::endl;
    std::cout << "2: No" << std::endl;
    std::cout << "=======================" << std::endl;

    std::getline(std::cin, plotCandlesticks);

    return plotCandlesticks;
}



std::string WeatherAnalyzerMain::getUserYear()
{
    std::string year;

    std::cout << "Enter a year between 1980 and 2019:" << std::endl;
    
    std::getline(std::cin, year);
    return year;
}


std::string WeatherAnalyzerMain::getUserMonth()
{
    std::string month;

    std::cout << "Enter a month between 01 and 12:" << std::endl;

    std::getline(std::cin, month);
    return month;
}


std::string WeatherAnalyzerMain::getUserDay()
{
    std::string day;

    std::cout << "Enter a day between 01 and 31:" << std::endl;

    std::getline(std::cin, day);
    return day;
}


std::string WeatherAnalyzerMain::getUserHour()
{
    std::string hour;

    std::cout << "Enter an hour between 00 and 23:" << std::endl;

    std::getline(std::cin, hour);
    return hour;
}