#include <iostream>
#include <memory>

#include "Bulb.hpp"


int main()
{
    Bulb bulb;

    bulb.ApplyVoltage(230);
    bulb.ApplyVoltage(330);
    bulb.ApplyVoltage(0);
}