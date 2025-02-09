#include "FSM.hpp"

FSM::FSM()
{

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
                mpCurrentState = transition->mToState;
            }
        }
    }
}

std::shared_ptr<State> FSM::GetCurrentState()
{
    return mpCurrentState;
}
