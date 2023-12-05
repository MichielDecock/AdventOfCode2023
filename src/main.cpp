#include <iostream>

#include "core_trebuchet_calibration.h"
#include "core_utils.h"

int main(int argc, char** argv)
{
    const auto   lines = core::readFile("res/calibration_input");
    const size_t sum = core::sum(core::extractNumbers(lines));

    std::cout << "The calibration sum is " << sum << std::endl;

    return 0;
}
