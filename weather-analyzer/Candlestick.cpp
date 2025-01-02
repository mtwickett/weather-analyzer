#include "Candlestick.h"



Candlestick::Candlestick(std::string _year, double _open, double _close, double _high, double _low)
    : year(_year), open(_open), close(_close), high(_high), low(_low)
{

}


const std::string& Candlestick::getYear() const {
    return year;
}

double Candlestick::getOpen() const {
    return open;
}

double Candlestick::getClose() const {
    return close;
}

double Candlestick::getHigh() const {
    return high;
}

double Candlestick::getLow() const {
    return low;
}