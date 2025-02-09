#pragma once

#include <memory>

#include "State.hpp"

class Transition
{
public:
    Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, int voltageCondition);
    bool CanTransition(int voltage) const;

// private:
    std::shared_ptr<State> mFromState;
    std::shared_ptr<State> mToState;
    int mVoltageCondition;
};