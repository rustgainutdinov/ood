#pragma once

#include <set>
#include <map>
#include <functional>

using namespace std;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template<typename T>
class IObserver
{
public:
    virtual void Update(T const &data) = 0;

    virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template<typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void RegisterObserver(IObserver<T> &observer, int priority) = 0;

    virtual void NotifyObservers() = 0;

    virtual void RemoveObserver(IObserver<T> &observer) = 0;

protected:
    virtual void UpdateObserver(IObserver<T> *observer, T data) = 0;
};

// Реализация интерфейса IObservable
template<class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType &observer, int priority) override
    {
        if (m_observers.find(priority) == m_observers.end())
        {
            m_observers[priority] = set<ObserverType *>{};
        }
        m_observers[priority].insert(&observer);
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        std::map<int, set<ObserverType *>> observersByPriority;
        copy(m_observers.begin(), m_observers.end(), inserter(observersByPriority, observersByPriority.begin()));
        auto it = observersByPriority.end();
        while (it != observersByPriority.begin())
        {
            it--;
            for (ObserverType *observer: it->second)
            {
                UpdateObserver(observer, data);
            }
        }
    }

    void RemoveObserver(ObserverType &observer) override
    {
        auto it = m_observers.begin();
        while (it != m_observers.end())
        {
            it->second.erase(&observer);
            it++;
        }
    }

protected:
    void UpdateObserver(ObserverType *observer, T data) override
    {
        observer->Update(data);
    }

    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData() const = 0;

    map<int, set<ObserverType *>> m_observers;
};
