#include "WeatherAnalyzerMain.h"
#include "Candlestick.h"
#include "Statistics.h"

#include <iomanip>
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
    std::string yearStart = candlesticks[0].year;
    std::string yearEnd = candlesticks.back().year;
    auto startIt = TemperatureRow::years.lower_bound(yearStart);
    auto endIt = TemperatureRow::years.upper_bound(yearEnd);
    
    std::cout << std::endl;
    
    for (const auto& pair : chart) {
        std::cout << std::setw(4)
            << pair.first << "   "
            << pair.second
            << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::string xAxis = "        ";
    for (auto it = startIt; it != endIt; ++it) {
        xAxis += it->first.substr(2, 2) + " ";
    }
    std::cout << "\n" << xAxis << std::endl;
}


void WeatherAnalyzerMain::plotCandlestickChart()
{
    std::vector<Candlestick> candlesticks = getCandlestickData();
    std::pair<std::string, std::string> yearRange = getUserYearRange();
    std::string yearStart = yearRange.first;
    std::string yearEnd = yearRange.second;
    int yearStartIndex = TemperatureRow::years.at(yearStart);
    int yearEndIndex = TemperatureRow::years.at(yearEnd);

    std::vector<Candlestick> filteredCandlesticks(
        candlesticks.begin() + yearStartIndex, 
        candlesticks.begin() + yearEndIndex + 1);
    std::cout << filteredCandlesticks.size() << std::endl;

    plotCandlestickChart(filteredCandlesticks);
}


void WeatherAnalyzerMain::printLineGraphData()
{
    std::string country = getUserCountry();
    unsigned int countryIndex = TemperatureRow::countries.at(country);
    std::string period = getUserPeriodFilter();

    
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
}


void WeatherAnalyzerMain::plotLineGraph()
{

}

////////////////// private methods ///////////////////////
std::string WeatherAnalyzerMain::getUserCountry()
{
    std::string country;
    do {
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

    } while (TemperatureRow::countries.find(country) == TemperatureRow::countries.end());
    
    std::cout << "You chose: " << country << std::endl;
    return country;
}


std::string WeatherAnalyzerMain::getUserPeriodFilter()
{
    std::string period;
    do {
        std::cout << "---Input instructions---" << std::endl;
        std::cout << "Choose period of data to be Year or Day" << std::endl;
        std::cout << "Please enter an option 1-2" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "1: Year" << std::endl;
        std::cout << "2: Day" << std::endl;
        std::cout << "=======================" << std::endl;

        std::getline(std::cin, period);
    } while (period != "1" && period != "2");
    
    return period;
}


std::string WeatherAnalyzerMain::getUserCandlestickOption()
{
    std::string answer;
    do {
        std::cout << std::endl;
        std::cout << "Would you like to plot the candlesticks?" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "1: Yes" << std::endl;
        std::cout << "2: No" << std::endl;
        std::cout << "=======================" << std::endl;

        std::getline(std::cin, answer);
    } while (answer != "1" && answer != "2");
    
    return answer;
}


std::pair<std::string, std::string> WeatherAnalyzerMain::getUserYearRange()
{
    std::string yearStart;
    std::string yearEnd;

    do {
        std::cout << "Choose a year range between 1980-2019 (inclusive)" << std::endl;
        std::cout << "Enter start year:" << std::endl;
        std::getline(std::cin, yearStart);
        std::cout << "Enter end year:" << std::endl;
        std::getline(std::cin, yearEnd);
    } while (TemperatureRow::years.find(yearStart) == TemperatureRow::years.end() ||
             TemperatureRow::years.find(yearEnd) == TemperatureRow::years.end());

    return { yearStart, yearEnd };
}



std::string WeatherAnalyzerMain::getUserYear()
{
    std::string year;
    do {
        std::cout << "Enter a year between 1980 and 2019:" << std::endl;
        std::getline(std::cin, year);
    } while (TemperatureRow::years.find(year) == TemperatureRow::years.end());
    
    return year;
}


std::string WeatherAnalyzerMain::getUserMonth()
{
    std::vector<std::string> months;
    for (int i = 1; i <= 12; ++i) {
        months.push_back((i < 10 ? "0" : "") + std::to_string(i));
    }
    std::string month;

    do {
        std::cout << "Enter a month between 01 and 12:" << std::endl;
        std::getline(std::cin, month);
    } while (std::find(months.begin(), months.end(), month) == months.end());
    
    return month;
}


std::string WeatherAnalyzerMain::getUserDay()
{
    std::vector<std::string> days;
    for (int i = 1; i <= 31; ++i) {
        days.push_back((i < 10 ? "0" : "") + std::to_string(i));
    }
    std::string day;

    do {
        std::cout << "Enter a day between 01 and 31:" << std::endl;
        std::getline(std::cin, day);
    } while (std::find(days.begin(), days.end(), day) == days.end());
    
    return day;
}


std::string WeatherAnalyzerMain::getUserHour()
{
    std::vector<std::string> hours;
    for (int i = 0; i <= 23; ++i) {
        hours.push_back((i < 10 ? "0" : "") + std::to_string(i));
    }
    std::string hour;

    do {
        std::cout << "Enter an hour between 00 and 23:" << std::endl;
        std::getline(std::cin, hour);
    } while (std::find(hours.begin(), hours.end(), hour) == hours.end());

    return hour;
}