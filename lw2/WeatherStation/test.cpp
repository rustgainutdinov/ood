#include <gtest/gtest.h>
#include "Observer.h"
#include "string"

using namespace std;

class CNotificationStatusKeeper : public IObserver<string>
{
private:
    void Update(string const &data) override
    {
        m_was_notified = true;
    }

    bool m_was_notified = false;
};

class CObserverWhichUnsubscribeWhileNotified : public IObserver<string>
{
    CObserverWhichUnsubscribeWhileNotified() {

    }
private:
    void Update(string const &data) override
    {
        m_was_notified = true;
    }

    CMockStringObservable
};

class CMockStringObservable : public CObservable<string>
{
protected:
    string GetChangedData() const override
    {
        return "some string";
    }
};

class TestCObservable : public ::testing::Test
{
};

TEST_F(TestCObservable, shouldNotifyObserversCorrectlyIfObserverRemoveHimselfWhileExecuting)
{
    CMockStringObservable observable = CMockStringObservable();
    observable
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}