#include <iostream>

#include "core_trebuchet_calibration.h"

int main(int argc, char** argv)
{
    const auto   lines = core::readInput("res/calibration_input");
    const size_t sum = core::sum(core::extractNumbers(lines));

    std::cout << "The calibration sum is " << sum << std::endl;

    return 0;
}
