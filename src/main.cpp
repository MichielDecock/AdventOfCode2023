#include <iostream>

#include "gondola_gear.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto lines = core::readFile("res/gondola_gear");

    const auto numbers = core::findGearNumbers(lines);

    const size_t sum = core::sum(numbers);

    std::cout << "The gondola gear sum is " << sum << std::endl;

    return 0;
}
