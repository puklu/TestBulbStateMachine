#include <iostream>
#include "State.hpp"

void State::OnEntry()
{ 
    std::cout << "Entered stage: " << StateToString(mName) << std::endl;
}

void State::OnExit()
{ 
    std::cout << "Exited stage: " << StateToString(mName) << std::endl;
}

OnState::OnState():State(eState::ON)
{
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


void BrokenState::DoWork()
{
    // while(true)
    // {
        std::cout << "Bulb is BROKEN" << std::endl;
    // }
}

std::string StateToString(eState state)
{
    switch (state)
    {
    case eState::ON:
        return "ON";

    case eState::OFF:
        return "OFF";

    case eState::BROKEN:
        return "BROKEN";
    
    default:
        return "UNKNOWN";
    }
}