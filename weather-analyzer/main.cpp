#include "WeatherAnalyzerMain.h"
#include <Windows.h>


int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	WeatherAnalyzerMain app{};
	app.init();
}