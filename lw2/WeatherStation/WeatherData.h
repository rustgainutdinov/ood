#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <cmath>
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

class IAccumulator
{
public:
    virtual void AddValue(double value) = 0;

    virtual double GetMin() const = 0;

    virtual double GetMax() const = 0;

    virtual double GetAverage() const = 0;

    virtual ~IAccumulator() = default;
};

class CStatsAccumulator : public IAccumulator
{
public:
    void AddValue(double value) override
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

    double GetMin() const override
    {
        return m_min;
    }

    double GetMax() const override
    {
        return m_max;
    }

    double GetAverage() const override
    {
        return m_acc / m_countAcc;
    }

private:
    double m_min = numeric_limits<double>::infinity();
    double m_max = -numeric_limits<double>::infinity();
    double m_acc = 0;
    unsigned m_countAcc = 0;
};

class CAngularStatsAccumulator : public IAccumulator
{
public:
    void AddValue(double value) override
    {
        if (m_min > value)
        {
            m_min = value;
        }
        if (m_max < value)
        {
            m_max = value;
        }
        m_acc.push_back(value);
        ++m_countAcc;
    }

    double GetMin() const override
    {
        return m_min;
    }

    double GetMax() const override
    {
        return m_max;
    }

    double GetAverage() const override
    {
        double x = 0, y = 0;
        for (double i: m_acc)
        {
            double rad = i * PI / 180.0;
            x += sin(rad);
            y += cos(rad);
        }
        return fmod((atan2(x / m_countAcc, y / m_countAcc) * (180.0 / PI) + 360.0), 360);
    }

private:
    const double PI = 3.141592653589793238463;
    double m_min = numeric_limits<double>::infinity();
    double m_max = -numeric_limits<double>::infinity();
    vector<double> m_acc;
    unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SFullWeatherInfo>
{
public:
    typedef IAccumulator AccumulatorType;

    CStatsDisplay()
    {
        m_statsAccumulators = {
                {GenerateKey(InsideKey, TemperatureKey),    NewCStatsAccumulator()},
                {GenerateKey(InsideKey, HumidityKey),       NewCStatsAccumulator()},
                {GenerateKey(InsideKey, PressureKey),       NewCStatsAccumulator()},
                {GenerateKey(OutsideKey, TemperatureKey),   NewCStatsAccumulator()},
                {GenerateKey(OutsideKey, HumidityKey),      NewCStatsAccumulator()},
                {GenerateKey(OutsideKey, PressureKey),      NewCStatsAccumulator()},
                {GenerateKey(OutsideKey, WindSpeedKey),     NewCStatsAccumulator()},
                {GenerateKey(OutsideKey, WindDirectionKey), NewCAngularStatsAccumulator()},
        };
    }

private:
    static CStatsAccumulator *NewCStatsAccumulator()
    {
        CStatsAccumulator *acc;
        acc = (CStatsAccumulator *) malloc(sizeof(CStatsAccumulator));
        new(acc) CStatsAccumulator;
        return acc;
    }

    static CAngularStatsAccumulator *NewCAngularStatsAccumulator()
    {
        CAngularStatsAccumulator *acc;
        acc = (CAngularStatsAccumulator *) malloc(sizeof(CAngularStatsAccumulator));
        new(acc) CAngularStatsAccumulator;
        return acc;
    }

    void Update(SFullWeatherInfo const &weatherInfo) override
    {
        map<string, double> m = FullWeatherInfoToMap(weatherInfo);
        auto it = m_statsAccumulators.begin();
        while (it != m_statsAccumulators.end())
        {
            it->second->AddValue(m.at(it->first));

            cout << "Max " << it->first << " " << it->second->GetMax() << endl;
            cout << "Min " << it->first << " " << it->second->GetMin() << endl;
            cout << "Average " << it->first << " " << it->second->GetAverage() << endl;
            cout << "---" << endl;
            it++;
        }
        cout << "----------------" << endl;
    }

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

    map<string, AccumulatorType *> m_statsAccumulators;
};

class CWeatherData : public CObservable<SFullWeatherInfo>
{
public:
    typedef IObserver<SFullWeatherInfo> ObserverType;

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

        fillChangedMeasurementKeys(measurements);
        MeasurementsChanged();
        clearChangedMeasurementKeys();
    }

    void RegisterObserver(ObserverType &observer, int priority, const string &measurementKey)
    {
        if (m_observer_measurement_key.find(&observer) == m_observer_measurement_key.end())
        {
            m_observer_measurement_key[&observer] = set<string>{};
        }
        m_observer_measurement_key[&observer].insert(measurementKey);
        CObservable::RegisterObserver(observer, priority);
    }

    void RemoveObserver(ObserverType &observer, const string &measurementKey)
    {
        m_observer_measurement_key[&observer].erase(measurementKey);
        CObservable::RemoveObserver(observer);
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

    void UpdateObserver(ObserverType *observer, SFullWeatherInfo data) override
    {
        auto it = m_changed_measurement_keys.begin();
        while (it != m_changed_measurement_keys.end())
        {
            if (m_observer_measurement_key[observer].find(*it) != m_observer_measurement_key[observer].end())
            {
                CObservable::UpdateObserver(observer, data);
                return;
            }
            it++;
        }
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

    void fillChangedMeasurementKeys(SMeasurements measurements)
    {
        if (measurements.temperature.wasSet)
        {
            m_changed_measurement_keys.insert(TemperatureKey);
        }
        if (measurements.humidity.wasSet)
        {
            m_changed_measurement_keys.insert(HumidityKey);
        }
        if (measurements.pressure.wasSet)
        {
            m_changed_measurement_keys.insert(PressureKey);
        }
        if (measurements.windSpeed.wasSet)
        {
            m_changed_measurement_keys.insert(WindSpeedKey);
        }
        if (measurements.windDirection.wasSet)
        {
            m_changed_measurement_keys.insert(WindDirectionKey);
        }
    }

    void clearChangedMeasurementKeys()
    {
        m_changed_measurement_keys.clear();
    }

    SBaseWeatherInfoProvider m_inside_info;
    SOutsideWeatherInfoProvider m_outside_info;
    map<ObserverType *, set<string>> m_observer_measurement_key;
    set<string> m_changed_measurement_keys;
};
