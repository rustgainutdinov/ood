#include <gtest/gtest.h>
#include "GumBallMachineWithState.h"

using namespace std;

class TestGumBallMachine : public ::testing::Test
{
};

TEST_F(TestGumBallMachine, shouldBeInSoldOutStateAfterCreation)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(0, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can't insert a quarter, the machine is sold out", str);
    m.EjectQuarters();
    getline(ss, str);
    ASSERT_EQ("You can't eject, you haven't inserted a quarter yet", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned but there's no gumballs", str);
}

TEST_F(TestGumBallMachine, shouldNotEjectQuarterIfQuarterNotInserted)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.EjectQuarters();
    getline(ss, str);
    ASSERT_EQ("You haven't inserted a quarter", str);
}

TEST_F(TestGumBallMachine, shouldNotTurnCrankIfQuarterNotInserted)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned but there's no quarter", str);
    getline(ss, str);
    ASSERT_EQ("You need to pay first", str);
}

TEST_F(TestGumBallMachine, shouldReleaseBall)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
}

TEST_F(TestGumBallMachine, shouldNotInsertQuarterIfBallsReleased)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    getline(ss, str);
    ASSERT_EQ("Oops, out of gumballs", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can't insert a quarter, the machine is sold out", str);
}

TEST_F(TestGumBallMachine, shouldReleaseAllBalls)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(2, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    getline(ss, str);
    ASSERT_EQ("Oops, out of gumballs", str);
}

TEST_F(TestGumBallMachine, shouldInsertQuarterIfQuarterAlreadyInserted)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.InsertQuarter();
    getline(ss, str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
}

TEST_F(TestGumBallMachine, shouldEjectAllQuartersIfQuartersAlreadyInserted)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.EjectQuarters();
    getline(ss, str);
    ASSERT_EQ("3 quarters returned", str);
}

TEST_F(TestGumBallMachine, shouldSwitchToHasQuaterStateAfterSoldOutIfQuartersInsertedBefore)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(3, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    getline(ss, str);
    ASSERT_EQ("Oops, out of gumballs", str);
}

TEST_F(TestGumBallMachine, shouldInsertAnotherQuartersAfterCrankTurned)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(2, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.EjectQuarters();
    getline(ss, str);
    ASSERT_EQ("2 quarters returned", str);
}

TEST_F(TestGumBallMachine, shouldEjectQuartersAfterAllBallsReleased)
{
    stringstream ss;
    string str;
    with_state::CGumballMachine m(1, ss);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You inserted a quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.InsertQuarter();
    getline(ss, str);
    ASSERT_EQ("You can insert another quarter", str);
    m.TurnCrank();
    getline(ss, str);
    ASSERT_EQ("You turned...", str);
    getline(ss, str);
    ASSERT_EQ("A gumball comes rolling out the slot...", str);
    getline(ss, str);
    ASSERT_EQ("Oops, out of gumballs", str);
    m.EjectQuarters();
    getline(ss, str);
    ASSERT_EQ("2 quarters returned", str);
}
