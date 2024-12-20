#include "WeatherAnalyzerMain.h"
#include "SearchData.h"
#include "TemperatureRow.h"


WeatherAnalyzerMain::WeatherAnalyzerMain()
{
    OPTIONS = {
        {"1", &WeatherAnalyzerMain::about},
        {"2", &WeatherAnalyzerMain::getTemperature}
    };
}


void WeatherAnalyzerMain::init()
{
    try
    {
        rows = CsvReader::readcsv(CsvReader::getFilePath("utc_timestamp,AT_temperature,BE_tem.txt"));
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


void WeatherAnalyzerMain::about()
{
    std::cout << "Check weather temperatures in European countries" << std::endl;
}


void WeatherAnalyzerMain::getTemperature()
{
    std::vector<std::string> prompts = { "country", "year", "month", "day", "hour"};
    std::vector<std::string> userInputs;

    std::cout << "---Input instructions---\n" << std::endl;
    std::cout << "Enter country as: (Austria)" << std::endl;
    std::cout << "Enter Year as: XXXX (1980-2019)" << std::endl;
    std::cout << "Enter Month as: XX (01-12)" << std::endl;
    std::cout << "Enter Day as: XX (01-31)" << std::endl;
    std::cout << "Enter Hour as: XX (00-23)" << std::endl;

    for (auto& prompt : prompts) {
        std::string input;
        std::cout << "Enter " << prompt << ": " << std::endl;
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

    double temp;
    try
    {
        int index = SearchData::getRowIndex(rows, timestamp);
        rows[index].temperatures[TemperatureRow::countries]
    }
    catch (const std::exception&)
    {

    }
    std::cout << 

}


void WeatherAnalyzerMain::printMenu()
{
    std::vector<std::string> MENU = {
        "=======================",
        "Please enter an option 1-6 or press e to exit",
        "=======================",
        "1: About",
        "2: Get a temperature",
        "3: Print Candlestick data",
        "4: Make a bid",
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