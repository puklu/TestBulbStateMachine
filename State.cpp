#include <iostream>
#include "State.hpp"

OnState::OnState():State(eState::ON)
{
}

void OnState::OnEntry()
{
    std::cout << "Entered ON state" << std::endl;
}

void OnState::OnExit()
{
    std::cout << "Exited ON state" << std::endl;
}

void OnState::DoWork()
{
    // while(true)
    // {
        std::cout << "Bulb is ON" << std::endl;
    // }
}

OffState::OffState():State(eState::OFF)
{
}

void OffState::OnEntry()
{
    std::cout << "Entered OFF state" << std::endl;
}

void OffState::OnExit()
{
    std::cout << "Exited OFF state" << std::endl;
}

void OffState::DoWork()
{
    // while(true)
    // {
        std::cout << "Bulb is OFF" << std::endl;
    // }
}

BrokenState::BrokenState():State(eState::BROKEN)
{
}

void BrokenState::OnEntry()
{
    std::cout << "Entered BROKEN state" << std::endl;
}

void BrokenState::OnExit()
{
    std::cout << "Exited BROKEN state" << std::endl;
}

void BrokenState::DoWork()
{
    // while(true)
    // {
        std::cout << "Bulb is BROKEN" << std::endl;
    // }
}