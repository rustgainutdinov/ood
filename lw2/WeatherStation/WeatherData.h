﻿#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include "Observer.h"

const std::string TemperatureKey = "temperature";
const std::string HumidityKey = "humidity";
const std::string PressureKey = "pressure";


struct SWeatherInfo {
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;

    //можно вынести в приватныц метод класса
    std::map<std::string, double> ToMap() const {
        std::map<std::string, double> m = {
                {TemperatureKey, temperature},
                {HumidityKey,    humidity},
                {PressureKey,    pressure}
        };
        return m;
    }
};

class CDisplay : public IObserver<SWeatherInfo> {
private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
        Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
        остается публичным
    */
    void Update(SWeatherInfo const &data) override {
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current PressureKey " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }
};

class CStatsAccumulator {
public:
    explicit CStatsAccumulator(std::string statsName) : m_statsName(std::move(statsName)) {}

    void AddValue(double value) {
        if (m_min > value) {
            m_min = value;
        }
        if (m_max < value) {
            m_max = value;
        }
        m_acc += value;
        ++m_countAcc;
    }

    //можно вынести в приватный метод класса
    void ShowStats() const {
        std::cout << "Max " << m_statsName << " " << m_max << std::endl;
        std::cout << "Min " << m_statsName << " " << m_min << std::endl;
        std::cout << "Average " << m_statsName << " " << (m_acc / m_countAcc) << std::endl;
    };

private:
    std::string m_statsName;
    double m_min = std::numeric_limits<double>::infinity();
    double m_max = -std::numeric_limits<double>::infinity();
    double m_acc = 0;
    unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo> {
public:
    CStatsDisplay() {
        m_statsAccumulators = {
                {TemperatureKey, CStatsAccumulator("Temperature")},
                {HumidityKey, CStatsAccumulator("Humidity")},
                {PressureKey, CStatsAccumulator("Pressure")},
        };
    }

private:
    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const &weatherInfo) override {
        std::map<std::string, double> m = weatherInfo.ToMap();
        for (auto &statsAccumulator: m_statsAccumulators) {
            statsAccumulator.second.AddValue(m.at(statsAccumulator.first));
            statsAccumulator.second.ShowStats();
        }
        std::cout << "----------------" << std::endl;
    }

    std::map<std::string, CStatsAccumulator> m_statsAccumulators;
};

class CWeatherData : public CObservable<SWeatherInfo> {
public:
    // Температура в градусах Цельсия
    double GetTemperature() const {
        return m_temperature;
    }

    // Относительная влажность (0...100)
    double GetHumidity() const {
        return m_humidity;
    }

    // Атмосферное давление (в мм.рт.ст)
    double GetPressure() const {
        return m_pressure;
    }

    void MeasurementsChanged() {
        NotifyObservers();
    }

    void SetMeasurements(double temp, double humidity, double pressure) {
        m_humidity = humidity;
        m_temperature = temp;
        m_pressure = pressure;

        MeasurementsChanged();
    }

protected:
    SWeatherInfo GetChangedData() const override {
        SWeatherInfo info;
        info.temperature = GetTemperature();
        info.humidity = GetHumidity();
        info.pressure = GetPressure();
        return info;
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};
