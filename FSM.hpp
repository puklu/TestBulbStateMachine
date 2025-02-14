#pragma once

#include <memory>
#include <vector>

class Bulb;
class State;
class Transition;

class FSM
{
public:
    FSM();
    void Initialize(std::shared_ptr<State> initial_state);
    void AddState(std::shared_ptr<State> state);
    void AddTransition(std::shared_ptr<Transition> transition);
    void HandleEvent(Bulb &bulb);
    std::shared_ptr<State> GetCurrentState();

// private:
    std::shared_ptr<State> mpCurrentState;
    std::vector<std::shared_ptr<State>> mAllStates;
    std::vector<std::shared_ptr<Transition>> mAllTransitions;
};
