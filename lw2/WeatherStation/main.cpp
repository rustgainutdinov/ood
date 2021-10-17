#include "WeatherData.h"

int main()
{
    CWeatherData wd;

    CDisplay display;
    wd.RegisterObserver(display, 0, WindDirectionKey);

    CStatsDisplay statsDisplay;
    wd.RegisterObserver(statsDisplay, 1, TemperatureKey);

    SMeasurements measurements = {
            true, true, 3, true, 0.7, true, 760,
            true, 20
    };
    wd.SetMeasurements(measurements);
    measurements.windDirection.wasSet = true;
    measurements.windDirection.value = 90;
    wd.SetMeasurements(measurements);
    wd.SetMeasurements(measurements);

    wd.RemoveObserver(statsDisplay, TemperatureKey);

    wd.SetMeasurements(measurements);
    wd.SetMeasurements(measurements);
    return 0;
}