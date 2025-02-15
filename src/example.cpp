#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

// Forward declarations
class State;
class Transition;

// Bulb class representing the bulb
class Bulb {
public:
    Bulb();
    void applyVoltage(float voltage);
    std::string getCurrentState() const;

private:
    std::shared_ptr<State> currentState;
    float currentVoltage = 0.0f; // Track the current voltage

    // Voltage-specific guard functions
    static bool isNormalVoltage(const Bulb* bulb);
    static bool isHighVoltage(const Bulb* bulb);
    static bool isLowVoltage(const Bulb* bulb);

    // Helper to create transitions
    std::shared_ptr<Transition> createTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, bool (*guard)(const Bulb*));
};

// State class representing a state in the FSM
class State {
public:
    explicit State(const std::string& name) : name(name) {}
    virtual ~State() = default;

    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void handleEvent(Bulb& bulb) = 0;

    std::string getName() const { return name; }

protected:
    std::string name;
};

// Transition class representing a transition between states
class Transition {
public:
    using GuardFunction = bool (*)(const Bulb*); // Function pointer for guard function

    Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, GuardFunction guard)
        : fromState(std::move(from)), toState(std::move(to)), guard(guard) {}

    bool canTransition(const Bulb* bulb) const {
        return guard(bulb); // Use the guard function to determine if the transition should occur
    }

    std::shared_ptr<State> getToState() const { return toState; }

private:
    std::shared_ptr<State> fromState;
    std::shared_ptr<State> toState;
    GuardFunction guard; // Function pointer to the guard function
};

// FSM class representing the Finite State Machine
class FSM {
public:
    void addState(std::shared_ptr<State> state);
    void addTransition(std::shared_ptr<Transition> transition);
    void setInitialState(std::shared_ptr<State> initialState);
    void handleEvent(Bulb& bulb);

private:
    std::unordered_map<std::string, std::shared_ptr<State>> states;
    std::vector<std::shared_ptr<Transition>> transitions;
    std::shared_ptr<State> currentState;
};

// Concrete states
class OffState : public State {
public:
    OffState() : State("Off") {}
    void handleEvent(Bulb& bulb) override;
};

class OnState : public State {
public:
    OnState() : State("On") {}
    void handleEvent(Bulb& bulb) override;
};

class BrokenState : public State {
public:
    BrokenState() : State("Broken") {}
    void handleEvent(Bulb& bulb) override;
};

// Bulb implementation
Bulb::Bulb() {
    // Initialize the FSM with the Off state
    currentState = std::make_shared<OffState>();

    // Create transitions with guard functions
    auto offState = std::make_shared<OffState>();
    auto onState = std::make_shared<OnState>();
    auto brokenState = std::make_shared<BrokenState>();

    auto offToOn = createTransition(offState, onState, &Bulb::isNormalVoltage);
    auto offToBroken = createTransition(offState, brokenState, &Bulb::isHighVoltage);
    auto onToOff = createTransition(onState, offState, &Bulb::isLowVoltage);
    auto onToBroken = createTransition(onState, brokenState, &Bulb::isHighVoltage);
}

void Bulb::applyVoltage(float voltage) {
    currentVoltage = voltage; // Update the current voltage
    currentState->handleEvent(*this); // Let the current state handle the event
}

std::string Bulb::getCurrentState() const {
    return currentState->getName();
}

std::shared_ptr<Transition> Bulb::createTransition(std::shared_ptr<State> from, std::shared_ptr<State> to, bool (*guard)(const Bulb*)) {
    return std::make_shared<Transition>(from, to, guard);
}

// Voltage-specific guard functions
bool Bulb::isNormalVoltage(const Bulb* bulb) {
    return bulb->currentVoltage >= 220 && bulb->currentVoltage <= 240;
}

bool Bulb::isHighVoltage(const Bulb* bulb) {
    return bulb->currentVoltage > 240;
}

bool Bulb::isLowVoltage(const Bulb* bulb) {
    return bulb->currentVoltage < 220;
}

// FSM implementation
void FSM::addState(std::shared_ptr<State> state) {
    states[state->getName()] = state;
}

void FSM::addTransition(std::shared_ptr<Transition> transition) {
    transitions.push_back(transition);
}

void FSM::setInitialState(std::shared_ptr<State> initialState) {
    currentState = initialState;
}

void FSM::handleEvent(Bulb& bulb) {
    for (const auto& transition : transitions) {
        if (transition->canTransition(&bulb) && currentState->getName() == transition->getToState()->getName()) {
            currentState->onExit();
            currentState = transition->getToState();
            currentState->onEnter();
            break;
        }
    }
}

// OffState implementation
void OffState::handleEvent(Bulb& bulb) {
    std::cout << "Bulb is Off. Checking for transitions...\n";
}

// OnState implementation
void OnState::handleEvent(Bulb& bulb) {
    std::cout << "Bulb is On. Checking for transitions...\n";
}

// BrokenState implementation
void BrokenState::handleEvent(Bulb& bulb) {
    std::cout << "Bulb is Broken and cannot change state.\n";
}

// Main function
int main() {
    Bulb bulb;

    bulb.applyVoltage(230);  // Should turn On
    std::cout << "Current State: " << bulb.getCurrentState() << "\n";

    bulb.applyVoltage(210);  // Should turn Off
    std::cout << "Current State: " << bulb.getCurrentState() << "\n";

    bulb.applyVoltage(250);  // Should break the bulb
    std::cout << "Current State: " << bulb.getCurrentState() << "\n";

    bulb.applyVoltage(230);  // Bulb is broken, no state change
    std::cout << "Current State: " << bulb.getCurrentState() << "\n";

    return 0;
}