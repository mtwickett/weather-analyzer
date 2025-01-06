// Related header
#include "WeatherAnalyzerMain.h"

// Standard library includes
#include <iomanip>
#include <thread>

// Project headers
#include "Statistics.h"
#include "ScatterPlotHighLow.h"
#include "Candlestick.h"


// Initialize the OPTIONS map with menu options the user can select as keys 
// and pointers to the member function that handles the option as values.
WeatherAnalyzerMain::WeatherAnalyzerMain()
{
    OPTIONS = {
        {"1", &WeatherAnalyzerMain::about},
        {"2", &WeatherAnalyzerMain::getTemperature},
        {"3", &WeatherAnalyzerMain::printCandlestickData},
        {"4", &WeatherAnalyzerMain::plotCandlestickChart},
        {"5", &WeatherAnalyzerMain::printScatterPlotData},
        {"6", &WeatherAnalyzerMain::plotScatterPlot},
        {"7", &WeatherAnalyzerMain::getPredictionTemp}
    };
}


void WeatherAnalyzerMain::init()
{
    try
    {
        // Attempt to read the csv file and create a TemperatureRow type for each row, store the rows in a vector
        rows = CsvReader::readcsv("weather_data_EU_1980-2019_temp_only.csv");
    }
    catch (const std::exception& e)
    {
        // Catch any exception thrown during the CSV file reading process and print an
        // error message to notify the user about the failure.
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // Display the menu and process user inputs in a loop until the user chooses to exit.
    do {
        // Display the menu options to the user.
        printMenu();
        // Process the user’s input and update the `option` member variable with the selected option.
        WeatherAnalyzerMain::option = processOption();

    } while (WeatherAnalyzerMain::option != "e"); // Exit the loop if the user selects "e" for exit.
    // Notify the user that the application is exiting the menu and closing.
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
        "4: View Candlestick Chart",
        "5: Print Scatter Plot Data",
        "6: View Scatter Plot",
        "7: Predict a high or low",
        "======================="
    };

    // Iterate through the menu options and print each one to the console.
    for (const auto& option : MENU) {
        std::cout << option << std::endl;
    }
}


std::string WeatherAnalyzerMain::processOption()
{
    std::string option;
    std::getline(std::cin, option);
    // Check if the input matches any valid options in the OPTIONS map.
    if (OPTIONS.find(option) != OPTIONS.end()) {
        std::cout << "You chose option " << option << ".\n" << std::endl; // print the user option
        (this->*OPTIONS[option])(); // dereference the pointer to the member function and call it on the current instance
    }
    // Handle invalid entries unless the user chooses to exit.
    else if (option != "e") {
        std::cout << "Invalid entry" << std::endl;
    }
    return option;
}


void WeatherAnalyzerMain::about()
{
    std::cout << "---About Section---" << std::endl;
    std::cout << "The dataset contains an hourly temperature in Degrees Celcius from 1980 to 2019" << std::endl;
    std::cout << "for 28 European countries. To determine the temperature, it uses a" << std::endl;
    std::cout << "population-weighted mean across all MERRA-2 grid cells within each country." << std::endl;
    std::cout << "The original dataset can be found here: https://data.open-power-system-data.org/weather_data/2020-09-16." << std::endl;
}


void WeatherAnalyzerMain::getTemperature()
{
    // call helper function to get user inputs.
    std::string country = getUserCountry();
    std::string year = getUserYear();
    std::string month = getUserMonth();
    std::string day = getUserDay();
    std::string hour = getUserHour();

    // Build a timestamp with the user inputs.
    std::string timestamp = year + "-" + month + "-" + day + "T" + hour + ":00:00Z";
  
    try
    {
        double temp;
        unsigned int rowIndex = TemperatureRow::getRowIndex(rows, timestamp); // Get the row index for the timestamp.
        unsigned int tempIndex = TemperatureRow::countries.at(country); // Get the column index for the country.
        temp = rows[rowIndex].TemperatureRow::getTemperatures()[tempIndex]; // Get the temperature
        std::cout << "\nCountry: " << country
                  << "\nDate: " << day << " " << months[month] << " " << year
                  << "\nTime: " << hour << ":00"
                  << "\nTemperature Degrees Celcius: " << temp 
                  << std::endl;
        
    }
    catch (const std::exception& e)
    {
        std::cout << "No data" << e.what() << std::endl;
    }
}

// get only the data for the candlesticks
std::vector<Candlestick> WeatherAnalyzerMain::getCandlestickData()
{
    getUserInput();
    // Get the country index if found.
    unsigned int countryIndex = 0;
    auto it = TemperatureRow::countries.find(country);
    if (it != TemperatureRow::countries.end()) {
        countryIndex = it->second;
    }
    else {
        std::cerr << "Error: No country at that index." << country << std::endl;
        throw std::runtime_error("Invalid country input.");
    }

    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<Candlestick> candlesticks;

    // If the period is "1" (Year), calculate candlesticks for each year.
    if (period == "1") {
        std::cout << "You chose Year" << std::endl;
        yearToTempsMap = TemperatureRow::getTempsByYear(rows, countryIndex); // Filter the data
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap); // Calculate each candlestick 
    }
    // If the period is "2" (Day of the year), calculate candlesticks for a day of each year.
    else {
        std::cout << "You chose Day" << std::endl;
        std::string monthDay = month + "-" + day;
        yearToTempsMap = TemperatureRow::getTempsByDayOfYear(rows, countryIndex, monthDay); // Filter the data
        candlesticks = Statistics::calculateCandlesticks(yearToTempsMap); // Calculate each candlestick 
    }

    return candlesticks;
}


void WeatherAnalyzerMain::printCandlestickData()
{
    // Call the above method to get the data.
    std::vector<Candlestick> candlesticks = getCandlestickData();

    // Print the candlestick data with 3 decimal places.
    std::cout << "YEAR |  OPEN |  CLOSE |  HIGH  |  LOW" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    for (const auto& c : candlesticks) {
        std::cout << std::fixed << std::setprecision(3) << 
            c.getYear() << " | " << c.getOpen() << " | " << c.getClose() <<
            " | " << c.getHigh() << " | " <<c.getLow() << std::endl;
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
    std::map<int, std::string, std::greater<int>> chart = Candlestick::getCandlestickChart(candlesticks);
    // Determine the range of years to be displayed on the x-axis based on the candlestick data.
    // Use the same method as the overloaded function below to avoid changing code.
    std::string yearStart = candlesticks[0].getYear(); // Get the first year
    std::string yearEnd = candlesticks.back().getYear(); // Get the last year
    // Create an iterator to print the x axis years (in this function there is no range but 
    // leaving it like this allows to easily add year range functionality)
    auto startIt = TemperatureRow::years.lower_bound(yearStart); 
    auto endIt = TemperatureRow::years.upper_bound(yearEnd);
    
    std::cout << std::endl;
    // Iterate over the map and print each y-axis line of candlestick data for every year
    for (const auto& pair : chart) {
        std::cout << std::setw(4)
            << pair.first << "   "
            << pair.second
            << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Slow the printing for effect
    }

    // Print the x axis years - used vertical to align with the candles
    std::string xAxisTop = "        ";
    std::string xAxisBottom = "        ";
    for (auto it = startIt; it != endIt; ++it) {
        xAxisTop += it->first.substr(2, 1) + "  ";
        xAxisBottom += it->first.substr(3, 1) + "  ";
    }
    std::cout << "\n" << xAxisTop << std::endl;
    std::cout << xAxisBottom << std::endl;
}


void WeatherAnalyzerMain::plotCandlestickChart()
{
    std::vector<Candlestick> candlesticks = getCandlestickData();
    // Get a user year range to filter the data by year
    std::pair<std::string, std::string> yearRange = getUserYearRange();
    std::string yearStart = yearRange.first;
    std::string yearEnd = yearRange.second;
    // Get the index for the start and end years in the candlesticks vector
    unsigned int yearStartIndex = TemperatureRow::years.at(yearStart);
    unsigned int yearEndIndex = TemperatureRow::years.at(yearEnd);

    // Create a new (filtered by year range) vector of candlesticks
    std::vector<Candlestick> filteredCandlesticks(
        candlesticks.begin() + yearStartIndex, 
        candlesticks.begin() + yearEndIndex + 1);

    // Call the above overloaded method of the same name with the filtered candlesticks 
    plotCandlestickChart(filteredCandlesticks);
}


std::vector<ScatterPlotHighLow> WeatherAnalyzerMain::getScatterPlotData()
{
    getUserInput();
    // Get the country index if found.
    unsigned int countryIndex = 0;
    auto it = TemperatureRow::countries.find(country);
    if (it != TemperatureRow::countries.end()) {
        countryIndex = it->second;
    }
    else {
        std::cerr << "Error: Invalid country entered: " << country << std::endl;
        throw std::runtime_error("Invalid country input.");
    }
    std::map<std::string, std::vector<double>> yearToTempsMap;
    std::vector<ScatterPlotHighLow> scatterPlot;

    // If the period is "1" (Year), calculate ScatterPlotHighLow for each year.
    if (period == "1") {
        yearToTempsMap = TemperatureRow::getTempsByYear(rows, countryIndex);
        scatterPlot = Statistics::calculateScatterPlotHighLows(yearToTempsMap);
    }
    // If the period is "2" (Day of the year), calculate ScatterPlotHighLow for a day of each year.
    else {
        std::string monthDay = month + "-" + day;
        yearToTempsMap = TemperatureRow::getTempsByDayOfYear(rows, countryIndex, monthDay);
        scatterPlot = Statistics::calculateScatterPlotHighLows(yearToTempsMap);
    }

    return scatterPlot;
}


void WeatherAnalyzerMain::printScatterPlotData()
{
    std::vector<ScatterPlotHighLow> scatterPlot = getScatterPlotData();

    // Print the ScatterPlotHighLow data with 3 decimal places.
    std::cout << "YEAR |  HIGH  |  LOW" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (const auto& p : scatterPlot) {
        std::cout << std::fixed << std::setprecision(3) <<
            p.getYear() << " | " << p.getHigh() << " | " << p.getLow() << std::endl;
    }
}


void WeatherAnalyzerMain::plotScatterPlot()
{
    std::vector<ScatterPlotHighLow> scatterPlot = getScatterPlotData();
    // Get a user year range to filter the data by year
    std::pair<std::string, std::string> yearRange = getUserYearRange();
    std::string yearStart = yearRange.first;
    std::string yearEnd = yearRange.second;
    // Get the index for the start and end years in the candlesticks vector
    unsigned int yearStartIndex = TemperatureRow::years.at(yearStart);
    unsigned int yearEndIndex = TemperatureRow::years.at(yearEnd);

    // Create a new (filtered by year range) vector of ScatterPlotHighLow objects
    std::vector<ScatterPlotHighLow> filteredScatterPlot(
        scatterPlot.begin() + yearStartIndex,
        scatterPlot.begin() + yearEndIndex + 1);

    // Create a map to store the plot
    std::map<int, std::string, std::greater<int>> plot;
    // Ask the user if they want high or low plotted.
    std::string highOrLow = getUserHighLow();
    if (highOrLow == "High") {
        // Calculate the plot with high values for the year range
        plot = ScatterPlotHighLow::calculateScatterPlotHighs(filteredScatterPlot);
    }
    else
        // Calculate the plot with low values for the year range
        plot = ScatterPlotHighLow::calculateScatterPlotLows(filteredScatterPlot);

    // Create an iterator to print the x axis years
    auto startIt = TemperatureRow::years.lower_bound(yearStart);
    auto endIt = TemperatureRow::years.upper_bound(yearEnd);

    std::cout << std::endl;
    // Iterate over the map and print each y-axis line of scatter plot data for every year
    for (const auto& pair : plot) {
        std::cout << std::setw(4)
            << pair.first << "    "
            << pair.second
            << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    // Print the x axis years - used vertical to align with the candles
    std::string xAxisTop = "        ";
    std::string xAxisBottom = "        ";
    for (auto it = startIt; it != endIt; ++it) {
        xAxisTop += it->first.substr(2, 1) + "  ";
        xAxisBottom += it->first.substr(3, 1) + "  ";
    }
    std::cout << "\n" << xAxisTop << std::endl;
    std::cout << xAxisBottom << std::endl;
}


void WeatherAnalyzerMain::getPredictionTemp()
{
    // Get scatter plot data for the selected country and period.
    std::vector<ScatterPlotHighLow> scatterPlot = getScatterPlotData();
    // Ask the user if they want to predict high or low temperatures.
    std::string extremumTemp = getUserHighLow();
    // Vector to store the prediction data (year and corresponding high/low).
    std::vector<std::pair<std::string, double>> predicationData;
    // Pushes year and either high or low data as a pair to the vector
    if (extremumTemp == "High") {
        for (const auto p : scatterPlot) {
            predicationData.push_back({ p.getYear(), p.getHigh()} );
        }
    }
    else {
        for (const auto p : scatterPlot) {
            predicationData.push_back({ p.getYear(), p.getLow() });
        }
    }
    
    // Calculates the correlation coefficient data
    double r = Statistics::getCorrelationCoefficient(predicationData);
    // if r is stronger than 0.7 or -0.7 then use simple linear regression to make the prediction
    if (r >= 0.7 || r <= -0.7) {
        std::cout << "The correlation coefficient (r) is strong: " << r << std::endl;
        std::cout << "(Prediction calculated using simple linear regression)." << std::endl;
        // Ask the user for a year to predict
        double predYear = getUserPredictionYear();
        // Predict the temperature using linear regression and round the value
        int predTemp = static_cast<int>(std::round(Statistics::getLinearRegressionPrediction(predicationData, predYear)));
        // The user choose yearly data
        if (period == "1") {
            std::cout << "\nCountry: " << country
                << "\n" << extremumTemp << " Temperature Degrees Celcius : " << predTemp
                << std::endl;
        }
        // The user chose a day of the year
        else {
            std::cout << "\nCountry: " << country
                << "\nDate: " << day << " " << months[month]
                << "\n" << extremumTemp << " Temperature Degrees Celcius : " << predTemp
                << std::endl;
        }
    }
    // If r is weaker make the prediction using the average from the previous years
    else {
        // average prediction
        std::cout << "The correlation coefficient (r) is weak: " << r << std::endl;
        std::cout << "(Prediction calculated using historical mean)." << std::endl;
        // Calculate the average
        double sum = 0.0;
        for (const auto& pair : predicationData) {
            sum += pair.second;
        }
        int average = static_cast<int>(std::round(sum / predicationData.size()));
        // The user choose yearly data
        if (period == "1") {
            std::cout << "\nCountry: " << country
                << "\n" << extremumTemp << " Temperature Degrees Celcius : " << average
                << std::endl;
        }
        // The user chose a day of the year
        else {
            std::cout << "\n---Yearly mean prediction---"
                << "\nCountry: " << country
                << "\nDate: " << day << " " << months[month]
                << "\n" << extremumTemp << " Temperature Degrees Celcius : " << average
                << std::endl;
        }
        
    }

}

////////////////// helper methods ///////////////////////

void WeatherAnalyzerMain::getUserInput()
{
    country = getUserCountry();
    period = getUserPeriodFilter();

    if (period != "1") {
        month = getUserMonth();
        day = getUserDay();
    }
}


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
        std::cout << "Choose a year range between 1980-2019 (inclusive)." << std::endl;
        std::cout << "Enter start year:" << std::endl;
        std::getline(std::cin, yearStart);
        std::cout << "Enter end year:" << std::endl;
        std::getline(std::cin, yearEnd);
    } while (TemperatureRow::years.find(yearStart) == TemperatureRow::years.end() ||
             TemperatureRow::years.find(yearEnd) == TemperatureRow::years.end());

    return { yearStart, yearEnd };
}


std::string WeatherAnalyzerMain::getUserHighLow()
{
    std::string answer;
    do {
        std::cout << std::endl;
        std::cout << "Would you like the high or low?" << std::endl;
        std::cout << "=======================" << std::endl;
        std::cout << "1: High" << std::endl;
        std::cout << "2: Low" << std::endl;
        std::cout << "=======================" << std::endl;

        std::getline(std::cin, answer);
    } while (answer != "1" && answer != "2");

    if (answer == "1")
        return "High";
    else
        return "Low";
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


double WeatherAnalyzerMain::getUserPredictionYear()
{
    std::string year;
    double yearNum = 0.0;
    do {
        std::cout << "What year would you like to predict?" << std::endl;
        std::getline(std::cin, year);
        yearNum = std::stod(year);
    } while (yearNum > 2019);

    return yearNum;
}