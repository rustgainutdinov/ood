#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace with_state
{

    struct IState
    {
        virtual void InsertQuarter() = 0;

        virtual void EjectQuarters() = 0;

        virtual void TurnCrank() = 0;

        virtual void Dispense() = 0;

        virtual std::string ToString() const = 0;

        virtual ~IState() = default;
    };

    struct IGumballMachine
    {
        virtual void ReleaseBall() = 0;

        virtual void ReleaseQuarters() = 0;

        virtual unsigned GetBallCount() const = 0;

        virtual unsigned GetQuartersCount() const = 0;

        virtual void IncQuarters() = 0;

        virtual void DecQuarters() = 0;

        virtual void SetSoldOutState() = 0;

        virtual void SetNoQuarterState() = 0;

        virtual void SetSoldState() = 0;

        virtual void SetHasQuartersState() = 0;

        virtual ~IGumballMachine() = default;
    };

    class CSoldState : public IState
    {
    public:
        CSoldState(IGumballMachine &gumballMachine, std::stringstream &stream)
                : m_gumballMachine(gumballMachine), m_stream(stream)
        {}

        void InsertQuarter() override
        {
            m_stream << "Please wait, we're already giving you a gumball\n";
        }

        void EjectQuarters() override
        {
            m_stream << "Sorry you already turned the crank\n";
        }

        void TurnCrank() override
        {
            m_stream << "Turning twice doesn't get you another gumball\n";
        }

        void Dispense() override
        {
            m_gumballMachine.ReleaseBall();
            if (m_gumballMachine.GetBallCount() == 0)
            {
                m_stream << "Oops, out of gumballs\n";
                m_gumballMachine.SetSoldOutState();
            }
            else if (m_gumballMachine.GetQuartersCount() > 0)
            {
                m_gumballMachine.SetHasQuartersState();
            }
            else
            {
                m_gumballMachine.SetNoQuarterState();
            }
        }

        std::string ToString() const override
        {
            return "delivering a gumball";
        }

    private:
        IGumballMachine &m_gumballMachine;
        std::stringstream &m_stream;
    };

    class CSoldOutState : public IState
    {
    public:
        CSoldOutState(IGumballMachine &gumballMachine, std::stringstream &stream)
                : m_gumballMachine(gumballMachine), m_stream(stream)
        {}

        void InsertQuarter() override
        {
            m_stream << "You can't insert a quarter, the machine is sold out\n";
        }

        void EjectQuarters() override
        {
            if (m_gumballMachine.GetQuartersCount() > 0)
            {
                m_gumballMachine.ReleaseQuarters();
            }
            else
            {
                m_stream << "You can't eject, you haven't inserted a quarter yet\n";
            }
        }

        void TurnCrank() override
        {
            m_stream << "You turned but there's no gumballs\n";
        }

        void Dispense() override
        {
            m_stream << "No gumball dispensed\n";
        }

        std::string ToString() const override
        {
            return "sold out";
        }

    private:
        IGumballMachine &m_gumballMachine;
        std::stringstream &m_stream;
    };

    class CHasQuartersState : public IState
    {
    public:
        CHasQuartersState(IGumballMachine &gumballMachine, std::stringstream &stream)
                : m_gumballMachine(gumballMachine), m_stream(stream)
        {}

        void InsertQuarter() override
        {
            m_stream << "You insert another quarter\n";
            m_gumballMachine.IncQuarters();
        }

        void EjectQuarters() override
        {
            m_gumballMachine.ReleaseQuarters();
            m_gumballMachine.SetNoQuarterState();
        }

        void TurnCrank() override
        {
            m_stream << "You turned...\n";
            m_gumballMachine.DecQuarters();
            m_gumballMachine.SetSoldState();
        }

        void Dispense() override
        {
            m_stream << "No gumball dispensed\n";
        }

        std::string ToString() const override
        {
            return "waiting for turn of crank";
        }

    private:
        IGumballMachine &m_gumballMachine;
        std::stringstream &m_stream;
    };

    class CNoQuarterState : public IState
    {
    public:
        CNoQuarterState(IGumballMachine &gumballMachine, std::stringstream &stream)
                : m_gumballMachine(gumballMachine), m_stream(stream)
        {}

        void InsertQuarter() override
        {
            m_stream << "You inserted a quarter\n";
            m_gumballMachine.IncQuarters();
            m_gumballMachine.SetHasQuartersState();
        }

        void EjectQuarters() override
        {
            m_stream << "You haven't inserted a quarter\n";
        }

        void TurnCrank() override
        {
            m_stream << "You turned but there's no quarter\n";
        }

        void Dispense() override
        {
            m_stream << "You need to pay first\n";
        }

        std::string ToString() const override
        {
            return "waiting for quarter";
        }

    private:
        IGumballMachine &m_gumballMachine;
        std::stringstream &m_stream;
    };

    class CGumballMachine : private IGumballMachine
    {
    public:
        CGumballMachine(unsigned numBalls, std::stringstream &stream)
                : m_soldState(*this, stream), m_soldOutState(*this, stream), m_noQuarterState(*this, stream),
                  m_hasQuartersState(*this, stream),
                  m_state(&m_soldOutState), m_count(numBalls), m_stream(stream)
        {
            if (m_count > 0)
            {
                m_state = &m_noQuarterState;
            }
        }

        void EjectQuarters()
        {
            m_state->EjectQuarters();
        }

        void InsertQuarter()
        {
            m_state->InsertQuarter();
        }

        void TurnCrank()
        {
            m_state->TurnCrank();
            m_state->Dispense();
        }

        std::string ToString() const
        {
            std::string s = "Mighty Gumball, Inc. C++\n-enabled Standing Gumball Model #2016 (with state)\nInventory: ";

            return s + std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "Machine is " +
                   m_state->ToString();
        }

    private:
        unsigned GetBallCount() const override
        {
            return m_count;
        }

        virtual void ReleaseBall() override
        {
            if (m_count != 0)
            {
                m_stream << "A gumball comes rolling out the slot...\n";
                --m_count;
            }
        }

        unsigned GetQuartersCount() const override
        {
            return m_quartersCount;
        }

        void IncQuarters() override
        {
            ++m_quartersCount;
        }

        void DecQuarters() override
        {
            if (m_quartersCount != 0)
            {
                --m_quartersCount;
            }
        }

        virtual void ReleaseQuarters() override
        {
            m_stream << std::to_string(GetQuartersCount()) << " quarters returned\n";
            m_quartersCount = 0;
        }

        void SetSoldOutState() override
        {
            m_state = &m_soldOutState;
        }

        void SetNoQuarterState() override
        {
            m_state = &m_noQuarterState;
        }

        void SetSoldState() override
        {
            m_state = &m_soldState;
        }

        void SetHasQuartersState() override
        {
            m_state = &m_hasQuartersState;
        }

    private:
        unsigned m_count = 0;
        unsigned m_quartersCount = 0;
        CSoldState m_soldState;
        CSoldOutState m_soldOutState;
        CNoQuarterState m_noQuarterState;
        CHasQuartersState m_hasQuartersState;
        IState *m_state;
        std::stringstream &m_stream;
    };

}
