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
        {"4", &WeatherAnalyzerMain::printCandlestickChart},
        {"5", &WeatherAnalyzerMain::printLineGraph}
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
        "2: Get a Temperature",
        "3: Print Candlestick Data",
        "4: Print Candlestick Chart",
        "5: Print Line Graph",
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
    // get country selection from user
    std::string userCountry;
    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Choose a country from the following selection:" << std::endl;
    for (const auto& pair : TemperatureRow::countries) {
        std::cout << pair.first << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    std::getline(std::cin, userCountry);
    std::string country = "";
    // convert each letter to uppercase
    for (auto& l : userCountry) {
        country += std::toupper(l);
    }

    std::vector<std::string> prompts = {
        "Choose a year between 1980 and 2019:", 
        "Choose a month between 01 and 12:", 
        "Choose a day between 01 and 31:", 
        "Choose an hour between 00 and 23:" 
    };
    std::vector<std::string> userInputs;

    for (auto& prompt : prompts) {
        std::string input;
        std::cout << prompt << std::endl;
        std::getline(std::cin, input);
        userInputs.push_back(input);
    }

    std::string timestamp = userInputs[0] +
        "-" +
        userInputs[1] +
        "-" +
        userInputs[2] +
        "T" +
        userInputs[3] +
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
        std::cout << "No data" << e.what() << std::endl;
    }
}


void WeatherAnalyzerMain::printCandlestickData()
{
    std::string country;
    std::string filter;

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
    unsigned int countryIndex = TemperatureRow::countries.at(country);

    // choose by day or year
    std::cout << "Choose filter by year or filter by day" << std::endl;
    std::cout << "For filter by year: Press 1" << std::endl;
    std::cout << "For filter by day: Press 2" << std::endl;
    std::getline(std::cin, filter);

    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<Candlestick> candlesticks;
    if (filter == "1") {
        yearToTempsMap = SearchData::getTempsByYear(rows, countryIndex);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
    }
    else if (filter == "2") {
        std::string day;
        std::cout << "Enter a month and day as: 01-01" << std::endl;
        std::getline(std::cin, day);
        yearToTempsMap = SearchData::getTempsByDayOfYear(rows, countryIndex, day);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
    }
    

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
    std::string filter;
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

    std::cout << "Choose a year range .eg. 1980-2019 or 1985-1990" << std::endl;
    std::getline(std::cin, range);


    std::string yearStartKey = range.substr(0, 4);
    std::string yearEndKey = range.substr(5, 4);
    int yearStart;
    int yearEnd;
    int yearRange;

    if (Candlestick::years.find(yearStartKey) != Candlestick::years.end() &&
        Candlestick::years.find(yearEndKey) != Candlestick::years.end()) {
        yearStart = Candlestick::years.at(yearStartKey);
        yearEnd = Candlestick::years.at(yearEndKey);
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
        yearToTempsMap = SearchData::getTempsByYear(rows, countryIndex);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
        chart = Statistics::getYearlyChartData(candlesticks, yearStart, yearRange);
    }
    else if (filter == "2") {
        std::string day;
        std::cout << "Enter a month and day as: 01-01" << std::endl;
        std::getline(std::cin, day);
        yearToTempsMap = SearchData::getTempsByDayOfYear(rows, countryIndex, day);
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap);
        try
        {
            chart = Statistics::getYearlyChartData(candlesticks, yearStart, yearRange);
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

    auto itStart = Candlestick::years.find(yearStartKey);
    auto itEnd = Candlestick::years.find(yearEndKey);
    if (itEnd != Candlestick::years.end()) {
        ++itEnd;
    }
    std::string xAxis = "        ";

    for (auto it = itStart; it != itEnd; ++it) {
        xAxis += it->first.substr(2, 2) + " ";
    }
    std::cout << "\n" << xAxis << std::endl;
}


void WeatherAnalyzerMain::printLineGraph()
{
    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<Candlestick> candlesticks;
    std::map<int, std::string, std::greater<int>> chart;

    // prompt user for a country  
    std::string country;
    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Choose a country from the following selection:" << std::endl;
    for (const auto& pair : TemperatureRow::countries) {
        std::cout << pair.second << ": " << pair.first << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    std::getline(std::cin, country);

    for (auto& u : country) {
        u = std::toupper(u);
    }

    std::cout << "You chose: " << country << "\n" << std::endl;
    unsigned int countryIndex = TemperatureRow::countries.at(country);

    std::string day;
    std::cout << "Enter a month and day as: 01-01" << std::endl;
    std::getline(std::cin, day);
    
    yearToTempsMap = SearchData::getTempsByDayOfYear(rows, countryIndex, day);
    for (const auto& pair : yearToTempsMap) {
        std::cout << pair.first << ": " << pair.second[0] << pair.second[1] << std::endl;
    }

}





