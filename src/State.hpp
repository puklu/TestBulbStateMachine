#pragma once
#include <string>

enum class eState
{
    ON,
    OFF,
    BROKEN
};

std::string StateToString(eState state);

class State
{
public:
    State(eState name): mName(name){}
    virtual ~State() = default;
    virtual void OnEntry();
    virtual void OnExit();
    virtual void DoWork() = 0;

protected:
    eState mName;
};

class OnState : public State
{
public:
    OnState();
    void DoWork() override; 
};

class OffState : public State
{
public:
    OffState();
    void DoWork() override; 
};

class BrokenState : public State
{
public:
    BrokenState();
    void DoWork() override; 
};
