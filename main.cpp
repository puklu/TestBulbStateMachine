#include <memory>

#include "FSM.hpp"
#include "State.hpp"
#include "Transition.hpp"

int main()
{
    
    std::shared_ptr<State> on_state = std::make_shared<OnState>();
    std::shared_ptr<State> off_state = std::make_shared<OffState>();
    std::shared_ptr<State> broken_state = std::make_shared<BrokenState>();
    
    std::shared_ptr<FSM> fsm = std::make_shared<FSM>(on_state);
    fsm->AddState(on_state);
    fsm->AddState(off_state);
    fsm->AddState(broken_state);

    std::shared_ptr<Transition> on_to_off = std::make_shared<Transition>(on_state, off_state, 0);
    std::shared_ptr<Transition> on_to_broken = std::make_shared<Transition>(on_state, broken_state, 300);
    std::shared_ptr<Transition> off_to_on = std::make_shared<Transition>(off_state, on_state, 230);
    std::shared_ptr<Transition> off_to_broken = std::make_shared<Transition>(off_state, broken_state, 300);
    std::shared_ptr<Transition> on_to_on = std::make_shared<Transition>(on_state, on_state, 230);
    std::shared_ptr<Transition> off_to_off = std::make_shared<Transition>(off_state, off_state, 0);

    fsm->AddTransition(on_to_off);
    fsm->AddTransition(on_to_broken);
    fsm->AddTransition(off_to_on);
    fsm->AddTransition(off_to_broken);
    fsm->AddTransition(on_to_on);
    fsm->AddTransition(off_to_off);

    fsm->TransitionToNextStage(230);
    fsm->TransitionToNextStage(0);
    fsm->TransitionToNextStage(230);
    fsm->TransitionToNextStage(300);
    fsm->TransitionToNextStage(0);

}