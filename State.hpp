#pragma once

enum class eState
{
    ON,
    OFF,
    BROKEN
};

class State
{
public:
    State(eState name): mName(name){}
    virtual void OnEntry() = 0;
    virtual void OnExit() = 0;
    virtual void DoWork() = 0;

// private:
    eState mName;
};

class OnState : public State
{
public:
    OnState();
    void OnEntry() override;
    void OnExit() override;
    void DoWork() override; 
};

class OffState : public State
{
public:
    OffState();
    void OnEntry() override;
    void OnExit() override;
    void DoWork() override; 
};

class BrokenState : public State
{
public:
    BrokenState();
    void OnEntry() override;
    void OnExit() override;
    void DoWork() override; 
};
