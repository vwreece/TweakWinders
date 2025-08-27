#include "strategies.h"
#include "reg_command.h"
#include <iostream>

void RunARegistryChange::RunCommand(const Registry_command& command) const
{
    std::cout << "Testing this strategy" << '\n';
}