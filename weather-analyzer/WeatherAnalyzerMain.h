// Ensure this header file is included only once
#pragma once

// Project headers
#include "TemperatureRow.h"
#include "csvReader.h"
#include "Candlestick.h"
#include "ScatterPlotHighLow.h"


class WeatherAnalyzerMain
{
public:
    WeatherAnalyzerMain();
    void init();

    // Access is only required within the class for the following data members and methods.
private:
    // Stores user-selected country
    std::string country = "";
    // Stores the user-selected time period filter.
    std::string period = "";
    // Stores the user-selected month.
    std::string month = "";
    // Stores the user-selected day.
    std::string day = "";
    
    ////////// Methods called by the user from the Menu ///////////
 
    // Prints information about the dataset
    void about();

    // Prints a temperature from an exact date and time.
    void getTemperature();

    // Prints candlestick data for a time period.
    void printCandlestickData();

    // Overloaded method.
    // Plots a candlestick chart using the printed data from the method above 
    void plotCandlestickChart(std::vector<Candlestick> candlesticks);

    // Overloaded method.
    // Plots a candlestick chart without the user printing the candlestick data first
    void plotCandlestickChart();

    // Prints scatter plot data for a time period.
    void printScatterPlotData();

    // Plots a scatter plot.
    void plotScatterPlot();

    // Calculates and displays temperature predictions.
    void getPredictionTemp();

    ////////////////////////////////////////////////////////////////


    // Prints the main menu to the user.
    void printMenu();

    // Calls a method from the user-selected menu option. Returns a user option that is saved globally.
    std::string processOption();

    // Stores the currently selected menu option from the processOption method.
    std::string option;

    // Calculates candlestick data. Returns a vector of Candlestick objects.
    std::vector<Candlestick> getCandlestickData();

    // Calculates scatter plot data. Returns a vector of ScatterPlotHighLow objects.
    std::vector<ScatterPlotHighLow> getScatterPlotData();

    //////////////// Helper Methods //////////////////

    // Gets user inputs for country, period, month, and day.
    void getUserInput();

    // Gets user input for country.
    std::string getUserCountry();

    // Gets user input for period filter (e.g., year or day of the year).
    std::string getUserPeriodFilter();

    // Asks user if they would like to view a candlestick chart for the menu option 3.
    std::string getUserCandlestickOption();

    // Gets user input for a year range.
    std::pair<std::string, std::string> getUserYearRange();

    // Asks user if they would like to view high or low data.
    std::string getUserHighLow();

    // Gets user input for year.
    std::string getUserYear();

    // Gets user input for month.
    std::string getUserMonth();

    // Gets user input for day.
    std::string getUserDay();

    // Gets user input for hour.
    std::string getUserHour();

    // Asks the user which year they would like to predict data for.
    double getUserPredictionYear();

    // Map linking menu options to corresponding member function pointers.
    std::map<std::string, void(WeatherAnalyzerMain::*)()> OPTIONS;

    // Stores rows of temperature data.
    std::vector<TemperatureRow> rows;


    // Maps month numbers to month names.
    std::map<std::string, std::string> months = {
        {"01", "January"}, {"02", "February"}, {"03", "March"}, {"04", "April"},
        {"05", "May"}, {"06", "June"}, {"07", "July"}, {"08", "August"},
        {"09", "September"}, {"10", "October"}, {"11", "November"}, {"12", "December"}
    };
};

