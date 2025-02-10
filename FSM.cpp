#include "FSM.hpp"

FSM::FSM(std::shared_ptr<State> state): mpCurrentState(std::move(state))
{
    AddState(state);
}

void FSM::AddState(std::shared_ptr<State> state)
{
    mAllStates.push_back(std::move(state));
}

void FSM::AddTransition(std::shared_ptr<Transition> transition)
{
    mAllTransitions.push_back(std::move(transition));
}

void FSM::TransitionToNextStage(int voltage)
{
    for(auto transition: mAllTransitions)
    {
        if(transition->mFromState == mpCurrentState)
        {
            if(transition->CanTransition(voltage))
            {
                mpCurrentState->OnExit();
                mpCurrentState = transition->mToState;
                mpCurrentState->OnEntry();
                mpCurrentState->DoWork();
                break;
            }
        }
    }
}

std::shared_ptr<State> FSM::GetCurrentState()
{
    return mpCurrentState;
}
