#include "WeatherAnalyzerMain.h"


WeatherAnalyzerMain::WeatherAnalyzerMain()
{
    OPTIONS = {
        {"1", &WeatherAnalyzerMain::instructions},
        {"2", &WeatherAnalyzerMain::getExchangeStats},
        {"3", &WeatherAnalyzerMain::makeAnAsk},
        {"4", &WeatherAnalyzerMain::makeABid},
        {"5", &WeatherAnalyzerMain::getWallet},
        {"6", &WeatherAnalyzerMain::getNextTimeFrame}
    };
}


void WeatherAnalyzerMain::init()
{
    std::string option;
    do {
        printMenu();
        option = processOption();

    } while (option != "e");
    std::cout << "Exiting options" << std::endl;
}


void WeatherAnalyzerMain::instructions()
{
    std::cout << "Your aim is to make money" << std::endl;
}


void WeatherAnalyzerMain::getExchangeStats()
{
    for (std::string const& p : orderBook.getProducts())
    {
        std::cout << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p,
            currentTime);

        double highPrice = orderBook.getHighPrice(entries);
        double lowPrice = orderBook.getLowPrice(entries);
        double averagePrice = orderBook.getAveragePrice(entries);
        double numberOfEntries = entries.size();
        double priceSpread = highPrice - lowPrice;


        std::cout << "There are " << numberOfEntries << " asks" << std::endl;
        std::cout << "High ask: " << highPrice << std::endl;
        std::cout << "Low ask: " << lowPrice << std::endl;
        std::cout << "Average ask: " << averagePrice << std::endl;
        std::cout << "Ask spread: " << priceSpread << std::endl;
    }
}


void WeatherAnalyzerMain::makeAnAsk()
{
    std::cout << "Make an ask: [product,price,amount] .eg. BTC/USDT,5000,0.3" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You choose: " << input << std::endl;

    std::vector<std::string> tokens = csvReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "You must enter 3 items" << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = csvReader::stringsToOBE(tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet contains funds - fulfilling order." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Insufficient funds." << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Bad Input: MerkelMain::makeAnAsk" << std::endl;
        }

    }

}


void WeatherAnalyzerMain::makeABid()
{
    std::cout << "Make an bid: [product,price,amount] .eg. BTC/USDT,5000,0.3" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You choose: " << input << std::endl;

    std::vector<std::string> tokens = csvReader::tokenize(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "You must enter 3 items" << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = csvReader::stringsToOBE(tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet contains funds - fulfilling order." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Insufficient funds." << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Bad Input: MerkelMain::makeAnBid" << std::endl;
        }

    }
}


void WeatherAnalyzerMain::getWallet()
{
    std::cout << wallet.toString() << std::endl;
}


void WeatherAnalyzerMain::getNextTimeFrame()
{
    std::cout << "Going to next time frame..." << std::endl;
    std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Total Sales: " << sales.size() << std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Price: " << sale.price << std::endl;
        std::cout << "Amount: " << sale.amount << std::endl;
    }

    currentTime = orderBook.getNextTime(currentTime);
}


void WeatherAnalyzerMain::printMenu()
{
    std::vector<std::string> MENU = {
        "=======================",
        "Please enter an option 1-6 or press e to exit",
        "=======================",
        "1: Print help",
        "2: Print exchange stats",
        "3: Make an ask",
        "4: Make a bid",
        "5: Print wallet",
        "6: Continue",
        "======================="
    };

    for (const auto& option : MENU) {
        std::cout << option << std::endl;
    }

    std::cout << "Current time: " << currentTime << std::endl;
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