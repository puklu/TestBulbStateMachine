#include "Transition.hpp"

Transition::Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, int voltageCondition):
    mFromState(std::move(from)),
    mToState(std::move(to)),
    mVoltageCondition(voltageCondition)
{
}

bool Transition::CanTransition(int voltage) const
{
    return voltage == mVoltageCondition; 
}
