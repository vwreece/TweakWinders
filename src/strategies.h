#pragma once
#include "reg_command.h"

//TODO: strategy shouldn't be bound to the Registry command type. We should be using some generic param. 
class Strategy
{
public: 
    virtual ~Strategy() = default;
    virtual void RunCommand(const Registry_command& command) const = 0;
};

class RunARegistryChange final : public Strategy {
public: 
    void RunCommand(const Registry_command& command) const override;
};

class StrategyFactory
{
    public:
    const Strategy* CurrentStrategy = nullptr;
};