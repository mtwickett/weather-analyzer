#include "Candlestick.h"



Candlestick::Candlestick(int _year, double _open, double _close, double _high, double _low)
    : year(_year), open(_open), close(_close), high(_high), low(_low)
{

}


double Candlestick::getAverage()
{
    return 0.5;
}
