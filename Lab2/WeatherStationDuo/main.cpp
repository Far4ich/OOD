#include "WeatherData.h"

int main()
{
	CWeatherData wdIn("in");
	CWeatherData wdOut("out");

	CDisplay display;
	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(display, 1);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761);

	return 0;
}
