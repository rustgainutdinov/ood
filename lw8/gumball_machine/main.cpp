#include "GumBallMachineWithState.h"

using namespace std;

template<typename GumballMachineType>
void TestGumballMachine(GumballMachineType &m)
{
    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.TurnCrank();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.EjectQuarters();
    m.TurnCrank();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();
    m.EjectQuarters();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();

    cout << m.ToString() << endl;
}

void TestGumballMachineWithState(std::stringstream &stream)
{

    with_state::CGumballMachine m(5, stream);
    TestGumballMachine(m);
}

int main()
{
    stringstream ss;
    TestGumballMachineWithState(ss);
    cout << ss.str();

    return 0;
}
