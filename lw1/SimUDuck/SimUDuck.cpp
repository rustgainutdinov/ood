#include <cassert>
#include <iostream>
#include <memory>

using namespace std;


struct IFlyBehavior
{
    virtual ~IFlyBehavior() = default;;

    virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
    void Fly() override
    {
        m_flights_count++;
        cout << "I'm flying for the " << m_flights_count << " time!!" << endl;
    }

private:
    int m_flights_count = 0;
};

class FlyNoWay : public IFlyBehavior
{
public:
    void Fly() override
    {}
};

struct IQuackBehavior
{
    virtual ~IQuackBehavior() = default;;

    virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
    void Quack() override
    {
        cout << "Quack squeak!!!" << endl;
    }
};

class SqueakBehavior : public IQuackBehavior
{
public:
    void Quack() override
    {
        cout << "Squeek!!!" << endl;
    }
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
    void Quack() override
    {}
};

struct IDanceBehavior
{
    virtual ~IDanceBehavior() = default;;

    virtual void Dance() = 0;
};

class DanceWaltz : public IDanceBehavior
{
public:
    void Dance() override
    {
        cout << "I'm dancing waltz" << endl;
    }
};

class DanceMenuet : public IDanceBehavior
{
public:
    void Dance() override
    {
        cout << "I'm dancing menuet" << endl;
    }
};

class DanceNoWay : public IDanceBehavior
{
public:
    void Dance() override
    {}
};

class Duck
{
public:
    Duck(unique_ptr<IFlyBehavior> &&flyBehavior,
         unique_ptr<IQuackBehavior> &&quackBehavior,
         unique_ptr<IDanceBehavior> &&danceBehavior)
    {
        assert(quackBehavior);
        assert(danceBehavior);
        SetFlyBehavior(move(flyBehavior));
        m_danceBehavior = move(danceBehavior);
        m_quackBehavior = move(quackBehavior);
    }

    void Quack() const
    {
        m_quackBehavior->Quack();
    }

    void Swim()
    {
        cout << "I'm swimming" << endl;
    }

    void Dance()
    {
        m_danceBehavior->Dance();
    }

    void Fly()
    {
        m_flyBehavior->Fly();
    }

    void SetFlyBehavior(unique_ptr<IFlyBehavior> &&flyBehavior)
    {
        assert(flyBehavior);
        m_flyBehavior = move(flyBehavior);
    }

    virtual void Display() const = 0;

    virtual ~Duck() = default;

private:
    unique_ptr<IFlyBehavior> m_flyBehavior;
    unique_ptr<IDanceBehavior> m_danceBehavior;
    unique_ptr<IQuackBehavior> m_quackBehavior;
};

class MallardDuck : public Duck
{
public:
    MallardDuck()
            : Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceWaltz>())
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
            : Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceMenuet>())
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
            : Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWay>())
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
            : Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<DanceNoWay>())
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
            : Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
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
    modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
    PlayWithDuck(modelDuck);
}
