#pragma once

#include <iostream>

namespace naive
{
    class CGumballMachine
    {
    public:
        enum class State
        {
            SoldOut,        // Жвачка закончилась
            NoQuarter,        // Нет монетки
            HasQuarter,        // Есть монетка
            Sold,            // Монетка выдана
        };

        CGumballMachine(unsigned count, std::stringstream &stream)
                : m_count(count), m_state(count > 0 ? State::NoQuarter : State::SoldOut), m_stream(stream)
        {
        }

        void InsertQuarter()
        {
            using namespace std;
            switch (m_state)
            {
                case State::SoldOut:
                    m_stream << "You can't insert a quarter, the machine is sold out\n";
                    break;
                case State::NoQuarter:
                    m_stream << "You inserted a quarter\n";
                    m_state = State::HasQuarter;
                    break;
                case State::HasQuarter:
                    m_stream << "You can't insert another quarter\n";
                    break;
                case State::Sold:
                    m_stream << "Please wait, we're already giving you a gumball\n";
                    break;
            }
        }

        void EjectQuarter()
        {
            using namespace std;
            switch (m_state)
            {
                case State::HasQuarter:
                    m_stream << "Quarter returned\n";
                    m_state = State::NoQuarter;
                    break;
                case State::NoQuarter:
                    m_stream << "You haven't inserted a quarter\n";
                    break;
                case State::Sold:
                    m_stream << "Sorry you already turned the crank\n";
                    break;
                case State::SoldOut:
                    m_stream << "You can't eject, you haven't inserted a quarter yet\n";
                    break;
            }
        }

        void TurnCrank()
        {
            using namespace std;
            switch (m_state)
            {
                case State::SoldOut:
                    m_stream << "You turned but there's no gumballs\n";
                    break;
                case State::NoQuarter:
                    m_stream << "You turned but there's no quarter\n";
                    break;
                case State::HasQuarter:
                    m_stream << "You turned...\n";
                    m_state = State::Sold;
                    Dispense();
                    break;
                case State::Sold:
                    m_stream << "Turning twice doesn't get you another gumball\n";
                    break;
            }
        }

        void Refill(unsigned numBalls)
        {
            m_count = numBalls;
            m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
        }

        std::string ToString() const
        {
            std::string state =
                    (m_state == State::SoldOut) ? "sold out" :
                    (m_state == State::NoQuarter) ? "waiting for quarter" :
                    (m_state == State::HasQuarter) ? "waiting for turn of crank"
                                                   : "delivering a gumball";
            std::string s = "Mighty Gumball, Inc. C++\n-enabled Standing Gumball Model #2016 (with state)\nInventory: ";

            return s + std::to_string(m_count) + " gumball" + (m_count != 1 ? "s" : "") + "Machine is " + state;
        }

    private:
        void Dispense()
        {
            using namespace std;
            switch (m_state)
            {
                case State::Sold:
                    m_stream << "A gumball comes rolling out the slot\n";
                    --m_count;
                    if (m_count == 0)
                    {
                        m_stream << "Oops, out of gumballs\n";
                        m_state = State::SoldOut;
                    }
                    else
                    {
                        m_state = State::NoQuarter;
                    }
                    break;
                case State::NoQuarter:
                    m_stream << "You need to pay first\n";
                    break;
                case State::SoldOut:
                case State::HasQuarter:
                    m_stream << "No gumball dispensed\n";
                    break;
            }
        }

        unsigned m_count;    // Количество шариков
        State m_state = State::SoldOut;
        std::stringstream &m_stream;
    };
}