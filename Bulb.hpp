#pragma once

#include <memory>
#include "State.hpp"
#include "Transition.hpp"

class FSM;

class Bulb
{
public:
    Bulb();
    ~Bulb();
    static bool IsNormalVoltage(const Bulb *bulb);
    static bool IsLowVoltage(const Bulb *bulb);
    static bool IsHighVoltage(const Bulb *bulb);
    std::shared_ptr<State> GetCurrentState();
    void ApplyVoltage(int voltage);

private:
    using GuardFunction = bool(*)(const Bulb*);
    std::shared_ptr<Transition> CreateTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, GuardFunction guard);

    std::unique_ptr<FSM> mFsm;
    std::shared_ptr<State> mpCurrentState;
    int mCurrentVoltage = 0;
};