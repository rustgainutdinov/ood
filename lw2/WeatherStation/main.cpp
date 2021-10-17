#include "WeatherData.h"

int main()
{
    CWeatherData wd;

    CDisplay display;
    wd.RegisterObserver(display, 0);

    CStatsDisplay statsDisplay;
    wd.RegisterObserver(statsDisplay, 1);

    SMeasurements measurements = {
            true, true, 3, true, 0.7, true, 760,
            true, 20, true, 270
    };
    wd.SetMeasurements(measurements);
    wd.SetMeasurements(measurements);

    wd.RemoveObserver(statsDisplay);

    wd.SetMeasurements(measurements);
    wd.SetMeasurements(measurements);
    return 0;
}