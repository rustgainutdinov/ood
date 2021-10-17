#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include "Observer.h"

using namespace std;

const string OutsideKey = "outside";
const string InsideKey = "inside";
const string TemperatureKey = "temperature";
const string HumidityKey = "humidity";
const string PressureKey = "pressure";
const string WindSpeedKey = "windSpeed";
const string WindDirectionKey = "windDirection";

struct SBaseWeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

struct SOutsideWeatherInfo : SBaseWeatherInfo
{
    double windSpeed = 0;
    double windDirection = 0;
};

struct SFullWeatherInfo
{
    SBaseWeatherInfo insideWeatherInfo;
    SOutsideWeatherInfo outsideWeatherInfo;
};

struct SMeasurements
{
    struct OptionalDouble
    {
        bool wasSet = false;
        double value = 0;
    };

    bool isOutside = false;
    OptionalDouble temperature;
    OptionalDouble humidity;
    OptionalDouble pressure;
    OptionalDouble windSpeed;
    OptionalDouble windDirection;
};

class CDisplay : public IObserver<SFullWeatherInfo>
{
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SFullWeatherInfo const &data) override
    {
        cout << "Current inside Temp " << data.insideWeatherInfo.temperature << endl;
        cout << "Current inside Hum " << data.insideWeatherInfo.humidity << endl;
        cout << "Current outside Pressure " << data.insideWeatherInfo.pressure << endl;
        cout << "Current outside Temp " << data.outsideWeatherInfo.temperature << endl;
        cout << "Current outside Hum " << data.outsideWeatherInfo.humidity << endl;
        cout << "Current outside Pressure " << data.outsideWeatherInfo.pressure << endl;
        cout << "Current outside Wind Speed " << data.outsideWeatherInfo.windSpeed << endl;
        cout << "Current outside Wind Direction " << data.outsideWeatherInfo.windDirection << endl;
        cout << "----------------" << endl;
    }
};

class CStatsAccumulator
{
public:
    void AddValue(double value)
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }
        m_acc += value;
        ++m_countAcc;
    }

    double GetMin() const
    {
        return m_min;
    }

    double GetMax() const
    {
        return m_min;
    }

    double GetAverage() const
    {
        return m_acc / m_countAcc;
    }

private:
    double m_min = numeric_limits<double>::infinity();
    double m_max = -numeric_limits<double>::infinity();
    double m_acc = 0;
    unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SFullWeatherInfo>
{
public:
    CStatsDisplay()
    {
        m_statsAccumulators = {
                {GenerateKey(InsideKey, TemperatureKey),    CStatsAccumulator()},
                {GenerateKey(InsideKey, HumidityKey),       CStatsAccumulator()},
                {GenerateKey(InsideKey, PressureKey),       CStatsAccumulator()},
                {GenerateKey(OutsideKey, TemperatureKey),   CStatsAccumulator()},
                {GenerateKey(OutsideKey, HumidityKey),      CStatsAccumulator()},
                {GenerateKey(OutsideKey, PressureKey),      CStatsAccumulator()},
                {GenerateKey(OutsideKey, WindSpeedKey),     CStatsAccumulator()},
                {GenerateKey(OutsideKey, WindDirectionKey), CStatsAccumulator()},
        };
    }

private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SFullWeatherInfo const &weatherInfo) override
    {
        map<string, double> m = FullWeatherInfoToMap(weatherInfo);
        for (auto &statsAccumulator: m_statsAccumulators)
        {
            statsAccumulator.second.AddValue(m.at(statsAccumulator.first));
            ShowStats(statsAccumulator.first, statsAccumulator.second);
            cout << "---" << endl;
        }
        cout << "----------------" << endl;
    }

    static void ShowStats(const string &statsKey, CStatsAccumulator statsAccumulator)
    {
        cout << "Max " << statsKey << " " << statsAccumulator.GetMax() << endl;
        cout << "Min " << statsKey << " " << statsAccumulator.GetMin() << endl;
        cout << "Average " << statsKey << " " << statsAccumulator.GetAverage() << endl;
    };

    static string GenerateKey(const string &sensorType, const string &parameterName)
    {
        return sensorType + " " + parameterName;
    }

    static map<string, double> FullWeatherInfoToMap(SFullWeatherInfo const &weatherInfo)
    {
        map<string, double> m = {
                {GenerateKey(InsideKey, TemperatureKey),    weatherInfo.insideWeatherInfo.temperature},
                {GenerateKey(InsideKey, HumidityKey),       weatherInfo.insideWeatherInfo.humidity},
                {GenerateKey(InsideKey, PressureKey),       weatherInfo.insideWeatherInfo.pressure},
                {GenerateKey(OutsideKey, TemperatureKey),   weatherInfo.outsideWeatherInfo.temperature},
                {GenerateKey(OutsideKey, HumidityKey),      weatherInfo.outsideWeatherInfo.humidity},
                {GenerateKey(OutsideKey, PressureKey),      weatherInfo.outsideWeatherInfo.pressure},
                {GenerateKey(OutsideKey, WindSpeedKey),     weatherInfo.outsideWeatherInfo.windSpeed},
                {GenerateKey(OutsideKey, WindDirectionKey), weatherInfo.outsideWeatherInfo.windDirection},
        };
        return m;
    }

    map<string, CStatsAccumulator> m_statsAccumulators;
};

class CWeatherData : public CObservable<SFullWeatherInfo>
{
public:
    void MeasurementsChanged()
    {
        NotifyObservers();
    }

    void SetMeasurements(SMeasurements measurements)
    {
        if (measurements.isOutside)
        {
            storeOutsideWeatherInfo(measurements);
        } else
        {
            storeInsideWeatherInfo(measurements);
        }

        MeasurementsChanged();
    }


protected:
    SFullWeatherInfo GetChangedData() const override
    {
        SBaseWeatherInfo insideInfo;
        SOutsideWeatherInfo outsideInfo;
        fillBaseWeatherInfo(insideInfo, m_inside_info);
        fillBaseWeatherInfo(outsideInfo, m_outside_info);
        outsideInfo.windSpeed = m_outside_info.windSpeed;
        outsideInfo.windDirection = m_outside_info.windDirection;

        SFullWeatherInfo info;
        info.insideWeatherInfo = insideInfo;
        info.outsideWeatherInfo = outsideInfo;
        return info;
    }


private:
    struct SBaseWeatherInfoProvider
    {
        double temperature = 0;
        double humidity = 0.5;
        double pressure = 760;
    };

    struct SOutsideWeatherInfoProvider : SBaseWeatherInfoProvider
    {
        double windSpeed = 0;
        double windDirection = 0;
    };

    static void fillBaseWeatherInfo(SBaseWeatherInfo &info, SBaseWeatherInfoProvider infoProvider)
    {
        info.temperature = infoProvider.temperature;
        info.humidity = infoProvider.humidity;
        info.pressure = infoProvider.pressure;
    };

    void storeInsideWeatherInfo(SMeasurements measurements)
    {
        SBaseWeatherInfoProvider info;
        fillBaseWeatherInfoProvider(info, m_inside_info, measurements);
        m_inside_info = info;
    };

    void storeOutsideWeatherInfo(SMeasurements measurements)
    {
        SOutsideWeatherInfoProvider info;
        fillBaseWeatherInfoProvider(info, m_outside_info, measurements);
        info.windSpeed = !measurements.windSpeed.wasSet ? m_outside_info.windSpeed : measurements.windSpeed.value;
        info.windDirection = !measurements.windDirection.wasSet ? m_outside_info.windDirection
                                                                : measurements.windDirection.value;
        m_outside_info = info;
    };

    static void fillBaseWeatherInfoProvider(SBaseWeatherInfoProvider &info, SBaseWeatherInfoProvider defaultInfo,
                                            SMeasurements measurements)
    {
        info.temperature =
                !measurements.temperature.wasSet ? defaultInfo.temperature : measurements.temperature.value;
        info.humidity = !measurements.humidity.wasSet ? defaultInfo.humidity : measurements.humidity.value;
        info.pressure = !measurements.pressure.wasSet ? defaultInfo.pressure : measurements.pressure.value;
    }

    SBaseWeatherInfoProvider m_inside_info;
    SOutsideWeatherInfoProvider m_outside_info;
};
