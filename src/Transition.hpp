#pragma once

#include <memory>

class Bulb;
class State;

typedef bool(*GuardFunction)(const Bulb*); // TODO: change the parameter to void*

class Transition
{
public:
    // Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, int voltageCondition);
    Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, GuardFunction guard);
    bool CanTransition(const Bulb* bulb) const;

// private:
    std::shared_ptr<State> mFromState;
    std::shared_ptr<State> mToState;
    // int mVoltageCondition;
    GuardFunction mGuard;
};