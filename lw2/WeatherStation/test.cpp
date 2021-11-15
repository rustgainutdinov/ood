#include <gtest/gtest.h>
#include "Observer.h"
#include "WeatherData.h"
#include "string"
#include <ctime>

using namespace std;


class CNotificationTimeKeeper : public IObserver<string>
{
public:
    time_t WhenNotified() const
    {
        return notifiedTime;
    }

private:
    void Update(string const &data) override
    {
        notifiedTime = time(0);
        sleep(1);
    }

    time_t notifiedTime{};
};

class CNotificationStatusKeeper : public IObserver<string>
{
public:
    bool WasNotified() const
    {
        return m_was_notified;
    }

private:
    void Update(string const &data) override
    {
        m_was_notified = true;
    }

    bool m_was_notified = false;
};

class CMockStringObservable : public CObservable<string>
{
public:
    bool HasObserver(ObserverType &observer)
    {
        auto it = m_observers.begin();
        while (it != m_observers.end())
        {
            if (it->second.find(&observer) != it->second.end())
            {
                return true;
            }
            it++;
        }
        return false;
    }

protected:
    string GetChangedData() const override
    {
        return "some string";
    }
};

class CObserverWhichUnsubscribeWhileNotified : public IObserver<string>
{
public:
    explicit CObserverWhichUnsubscribeWhileNotified(CMockStringObservable *observable) : m_observable(observable)
    {}

private:
    void Update(string const &data) override
    {
        m_observable->RemoveObserver(*this);
    }

    CMockStringObservable *m_observable;
};

class CObserverMeasurementKeeper : public IObserver<SFullWeatherInfo>
{
public:
    SFullWeatherInfo GetLastWeatherInfo()
    {
        return lastWeatherInfo;
    }

private:
    void Update(SFullWeatherInfo const &data) override
    {
        lastWeatherInfo = data;
    }

    SFullWeatherInfo lastWeatherInfo;
};

class TestCObservable : public ::testing::Test
{
};

class TestCWeatherData : public ::testing::Test
{
};

TEST_F(TestCObservable, shouldNotifyObserversCorrectlyIfObserverRemoveHimselfWhileExecuting)
{
    CMockStringObservable observable = CMockStringObservable();
    CNotificationStatusKeeper observer0 = CNotificationStatusKeeper();
    CObserverWhichUnsubscribeWhileNotified observer1 = CObserverWhichUnsubscribeWhileNotified(&observable);
    CNotificationStatusKeeper observer2 = CNotificationStatusKeeper();

    observable.RegisterObserver(observer0, 0);
    observable.RegisterObserver(observer1, 1);
    observable.RegisterObserver(observer2, 2);

    ASSERT_TRUE(observable.HasObserver(observer1));
    observable.NotifyObservers();

    ASSERT_FALSE(observable.HasObserver(observer1));
    ASSERT_TRUE(observer0.WasNotified());
    ASSERT_TRUE(observer2.WasNotified());
}

TEST_F(TestCObservable, shouldNotifyObserversByPriority)
{
    CMockStringObservable observable = CMockStringObservable();
    CNotificationTimeKeeper observer0 = CNotificationTimeKeeper();
    CNotificationTimeKeeper observer1 = CNotificationTimeKeeper();

    observable.RegisterObserver(observer0, 0);
    observable.RegisterObserver(observer1, 1);
    observable.NotifyObservers();
    ASSERT_TRUE(observer0.WhenNotified() > observer1.WhenNotified());
}

TEST_F(TestCWeatherData, shouldStoreLastMeasurements)
{
    CWeatherData weatherData = CWeatherData();
    CObserverMeasurementKeeper observer0 = CObserverMeasurementKeeper();
    weatherData.RegisterObserver(observer0, 0, "key");
    const int temperature = 35;
    SMeasurements measurements = {true, true, temperature};
    weatherData.SetMeasurements(measurements);
    ASSERT_TRUE(observer0.GetLastWeatherInfo().outsideWeatherInfo.temperature == temperature);
    measurements.temperature.wasSet = false;
    weatherData.SetMeasurements(measurements);
    measurements.temperature.value = 0;
    measurements.temperature.wasSet = true;
    measurements.isOutside = false;
    weatherData.SetMeasurements(measurements);
    ASSERT_TRUE(observer0.GetLastWeatherInfo().outsideWeatherInfo.temperature == temperature);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}