#include "Bulb.hpp"
#include "FSM.hpp"

Bulb::Bulb()
{
    mFsm = std::make_unique<FSM>();

    std::shared_ptr<State> on_state = std::make_shared<OnState>();
    std::shared_ptr<State> off_state = std::make_shared<OffState>();
    std::shared_ptr<State> broken_state = std::make_shared<BrokenState>();

    mFsm->AddState(on_state);
    mFsm->AddState(off_state);
    mFsm->AddState(broken_state);

    
    std::shared_ptr<Transition> guard_on_to_off = CreateTransition(on_state, off_state, IsLowVoltage);
    std::shared_ptr<Transition> guard_on_to_broken = CreateTransition(on_state, broken_state, IsHighVoltage);
    std::shared_ptr<Transition> guard_off_to_on = CreateTransition(off_state, on_state, IsNormalVoltage);
    std::shared_ptr<Transition> guard_off_to_broken = CreateTransition(off_state, broken_state, IsHighVoltage);
    
    mFsm->AddTransition(guard_on_to_off);
    mFsm->AddTransition(guard_on_to_broken);
    mFsm->AddTransition(guard_off_to_on);
    mFsm->AddTransition(guard_off_to_broken);
    
    mpCurrentState = off_state;

    mFsm->Initialize(mpCurrentState);
}

bool Bulb::IsNormalVoltage(const Bulb *bulb)
{
    return (bulb->mCurrentVoltage >=220 && bulb->mCurrentVoltage <=240);
}

bool Bulb::IsLowVoltage(const Bulb *bulb)
{
    return bulb->mCurrentVoltage < 220;
}

bool Bulb::IsHighVoltage(const Bulb *bulb)
{
    return bulb->mCurrentVoltage > 240;
}

std::shared_ptr<Transition> Bulb::CreateTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, GuardFunction guard)
{
    return std::make_shared<Transition>(from, to, guard);
}

void Bulb::ApplyVoltage(int voltage)
{
    mCurrentVoltage = voltage;
    mFsm->HandleEvent(*this);
}

std::shared_ptr<State> Bulb::GetCurrentState()
{
    return mpCurrentState;
}

Bulb::~Bulb() = default;
