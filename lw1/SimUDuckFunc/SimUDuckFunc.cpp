#include <cassert>
#include <iostream>
#include <functional>
#include <utility>

using namespace std;

struct IFlyBehavior
{
    virtual ~IFlyBehavior() = default;;

    virtual void Fly() = 0;
};

struct FlyWithWings
{
    FlyWithWings() = default;

    void operator()()
    {
        m_flights_count++;
        cout << "I'm flying for the " << m_flights_count << " notifiedTime!!" << endl;
    }

private:
    int m_flights_count = 0;
};

void fly()
{
    cout << "I'm flying for the notifiedTime!!" << endl;
}

void flyNoWay()
{}

void quack()
{
    cout << "Quack squeak!!!" << endl;
}

void squeak()
{
    cout << "Squeek!!!" << endl;
}

void quackNoWay()
{}

void danceWaltz()
{
    cout << "I'm dancing waltz" << endl;
}

void danceMenuet()
{
    cout << "I'm dancing menuet" << endl;
}

void danceNoWay()
{}

class Duck
{
public:
    Duck(function<void()> flyingMethod,
         function<void()> quackingMethod,
         function<void()> dancingMethod)
    {
        assert(quackingMethod);
        assert(dancingMethod);
        SetFlyBehavior(std::move(flyingMethod));
        m_quackingMethod = std::move(quackingMethod);
        m_dancingMethod = std::move(dancingMethod);
    }

    void Quack() const
    {
        return m_quackingMethod();
    }

    void Swim()
    {
        cout << "I'm swimming" << endl;
    }

    void Dance()
    {
        return m_dancingMethod();
    }

    void Fly()
    {
        return m_flyingMethod();
    }

    void SetFlyBehavior(function<void()> flyingMethod)
    {
        m_flyingMethod = std::move(flyingMethod);
    }

    virtual void Display() const = 0;

    virtual ~Duck() = default;

private:
    function<void()> m_flyingMethod;
    function<void()> m_quackingMethod;
    function<void()> m_dancingMethod;
};

class MallardDuck : public Duck
{
public:
    MallardDuck() : Duck(FlyWithWings(), quack, danceWaltz)
    {
    }

    void Display() const override
    {
        cout << "I'm mallard duck" << endl;
    }
};

class RedheadDuck : public Duck
{
public:
    RedheadDuck()
            : Duck(FlyWithWings(), quack, danceMenuet)
    {
    }

    void Display() const override
    {
        cout << "I'm redhead duck" << endl;
    }
};

class DecoyDuck : public Duck
{
public:
    DecoyDuck()
            : Duck(flyNoWay, quackNoWay, danceNoWay)
    {
    }

    void Display() const override
    {
        cout << "I'm decoy duck" << endl;
    }
};

class RubberDuck : public Duck
{
public:
    RubberDuck()
            : Duck(flyNoWay, squeak, danceNoWay)
    {
    }

    void Display() const override
    {
        cout << "I'm rubber duck" << endl;
    }
};

class ModelDuck : public Duck
{
public:
    ModelDuck()
            : Duck(flyNoWay, quack, danceNoWay)
    {
    }

    void Display() const override
    {
        cout << "I'm model duck" << endl;
    }
};

void DrawDuck(Duck const &duck)
{
    duck.Display();
}

void PlayWithDuck(Duck &duck)
{
    DrawDuck(duck);
    duck.Quack();
    duck.Fly();
    duck.Fly();
    duck.Dance();
    cout << endl;
}

int main()
{
    MallardDuck mallardDuck;
    PlayWithDuck(mallardDuck);

    RedheadDuck redheadDuck;
    PlayWithDuck(redheadDuck);

    RubberDuck rubberDuck;
    PlayWithDuck(rubberDuck);

    DecoyDuck decoyDuck;
    PlayWithDuck(decoyDuck);

    ModelDuck modelDuck;
    PlayWithDuck(modelDuck);
    modelDuck.SetFlyBehavior(FlyWithWings());
    PlayWithDuck(modelDuck);
}
