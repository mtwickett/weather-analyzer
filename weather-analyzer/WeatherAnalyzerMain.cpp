#include "WeatherAnalyzerMain.h"
#include "Candlestick.h"
#include "Statistics.h"

#include <iomanip>
#include <iostream>


WeatherAnalyzerMain::WeatherAnalyzerMain()
{
    OPTIONS = {
        {"1", &WeatherAnalyzerMain::about},
        {"2", &WeatherAnalyzerMain::getTemperature},
        {"3", &WeatherAnalyzerMain::printCandlestickData},
        {"4", &WeatherAnalyzerMain::printCandlestickChart}
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

    std::string option;
    do {
        printMenu();
        option = processOption();

    } while (option != "e");
    std::cout << "Exiting options" << std::endl;
}


void WeatherAnalyzerMain::printMenu()
{
    std::vector<std::string> MENU = {
        "\n=======================",
        "Please enter an option 1-6 or press e to exit",
        "=======================",
        "1: About",
        "2: Get a temperature",
        "3: Print Candlestick data",
        "4: Print Candlestick Chart",
        "5: Print wallet",
        "6: Continue",
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
        std::cout << "You choose option " << option << "." << std::endl;
        (this->*OPTIONS[option])();
    }
    else if (option != "e") {
        std::cout << "Invalid entry" << std::endl;
    }
    return option;
}


void WeatherAnalyzerMain::about()
{
    std::cout << "Check weather temperatures in European countries" << std::endl;
}


void WeatherAnalyzerMain::getTemperature()
{
    std::vector<std::string> prompts = { 
        "Enter country as: (Austria)", 
        "Enter Year as: XXXX (1980-2019)", 
        "Enter Month as: XX (01-12)", 
        "Enter Day as: XX (01-31)", 
        "Enter Hour as: XX (00-23)" };
    std::vector<std::string> userInputs;

    std::cout << "---Input instructions---\n" << std::endl;
    for (auto& prompt : prompts) {
        std::string input;
        std::cout << prompt << std::endl;
        std::getline(std::cin, input);
        userInputs.push_back(input);
    }
    
    std::string country;
    for (auto& u : userInputs[0]) {
        country += std::toupper(u);
    }


    std::string timestamp = userInputs[1] +
        "-" +
        userInputs[2] +
        "-" +
        userInputs[3] +
        "T" +
        userInputs[4] +
        ":00:00Z";

    std::cout << "You chose " << country << " at " << timestamp << std::endl;

    double temp;
    try
    {
        int rowIndex = SearchData::getRowIndex(rows, timestamp);
        unsigned int tempIndex = TemperatureRow::countries.at(country);
        temp = rows[rowIndex].temperatures[tempIndex];
        std::cout << "Temperature Degrees Celcius: " << temp << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "didn't work" << e.what() << std::endl;
    }
}


void WeatherAnalyzerMain::printCandlestickData()
{
    std::string country;

    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Enter country as: (Austria)" << std::endl;
    std::getline(std::cin, country);
    for (auto& u : country) {
        u = std::toupper(u);
    }

    std::cout << "You chose: " << country << std::endl;
    unsigned int countryIndex = TemperatureRow::countries.at(country);
    std::map<std::string, std::vector<double>> yearToTempsMap = SearchData::getTempsByYear(rows, countryIndex);

    std::vector<Candlestick> candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);

    std::cout << "YEAR |  OPEN |  CLOSE |  HIGH  |  LOW" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    for (const auto& c : candlesticks) {
        std::cout << std::fixed << std::setprecision(3) << 
            c.year << " | " << c.open << " | " << c.close <<
            " | " << c.high << " | " <<c.low << std::endl;
    }
}


void WeatherAnalyzerMain::printCandlestickChart()
{
    std::string country;
    std::string range;
    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Enter country as: (Austria)" << std::endl;
    std::getline(std::cin, country);

    std::cout << "Enter a year range (max 20) as: 1980-1999" << std::endl;
    std::getline(std::cin, range);

    for (auto& u : country) {
        u = std::toupper(u);
    }

    std::string yearStartKey = range.substr(0, 4);
    std::string yearEndKey = range.substr(5);
    unsigned int yearStart = 0;
    unsigned int yearEnd = 0;

    if (Candlestick::years.find(yearStartKey) != Candlestick::years.end() &&
        Candlestick::years.find(yearEndKey) != Candlestick::years.end()) {
        yearStart = Candlestick::years.at(yearStartKey);
        yearEnd = Candlestick::years.at(yearEndKey) + 1;

    }
    else {
        std::cerr << "One or both years not found in the map." << std::endl;
    }

    std::cout << "You chose: " << country << std::endl;
    unsigned int countryIndex = TemperatureRow::countries.at(country);
    std::map<std::string, std::vector<double>> yearToTempsMap = SearchData::getTempsByYear(rows, countryIndex);

    std::vector<Candlestick> candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);

    std::map<int, std::string, std::greater<int>> test = Statistics::getChartData(candlesticks, yearStart, yearEnd);

    for (const auto& pair : test) {
        std::cout << std::setw(4) << pair.first << "   " << pair.second << std::endl;
    }

    auto itStart = Candlestick::years.find(yearStartKey);
    auto itEnd = Candlestick::years.find(yearEndKey);
    if (itEnd != Candlestick::years.end()) {
        ++itEnd;
    }
    std::string xAxis = "         ";

    for (auto it = itStart; it != itEnd; ++it) {
        xAxis += it->first + " ";
    }
    std::cout << "\n" << xAxis << std::endl;
}


