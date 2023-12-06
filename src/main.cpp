#include <iostream>

#include "gondola_gear.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto lines = core::readFile("res/gondola_gear");

    const auto ratios = core::extractGearRatios(lines);

    const size_t sum = core::sum(ratios);

    std::cout << "The gondola gear ratio sum is " << sum << std::endl;

    return 0;
}
