#pragma once

#include <memory>
#include <vector>
#include "State.hpp"
#include "Transition.hpp"

class FSM
{
public:
    FSM();
    void AddState(std::shared_ptr<State> state);
    void AddTransition(std::shared_ptr<Transition> transition);
    void TransitionToNextStage(int voltage);
    std::shared_ptr<State> GetCurrentState();

// private:
    std::shared_ptr<State> mpCurrentState;
    std::vector<std::shared_ptr<State>> mAllStates;
    std::vector<std::shared_ptr<Transition>> mAllTransitions;
};
