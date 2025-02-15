#include "FSM.hpp"
#include "State.hpp"
#include "Transition.hpp"

FSM::FSM()
{

}

void FSM::Initialize(std::shared_ptr<State> initial_state)
{
    mpCurrentState = std::move(initial_state);
    mAllStates.push_back(std::move(initial_state));  
}

void FSM::AddState(std::shared_ptr<State> state)
{
    mAllStates.push_back(std::move(state));
}

void FSM::AddTransition(std::shared_ptr<Transition> transition)
{
    mAllTransitions.push_back(std::move(transition));
}


void FSM::HandleEvent(Bulb &bulb)
{
    for(auto transition: mAllTransitions)
    {
        if(transition->mFromState == mpCurrentState)
        {
            if(transition->CanTransition(&bulb))
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
