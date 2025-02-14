#include "Transition.hpp"

// Transition::Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, int voltageCondition):
Transition::Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, GuardFunction guard):
    mFromState(std::move(from)),
    mToState(std::move(to)),
    // mVoltageCondition(voltageCondition)
    mGuard(guard)
{
}

bool Transition::CanTransition(const Bulb* bulb) const
{
    return mGuard(bulb);
}
