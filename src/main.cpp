#include <iostream>

#include "scratchcard.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto cards = core::numberOfScratchCards("res/scratchcard");

    const size_t sum = core::sum(cards);

    std::cout << "The sum is " << sum << std::endl;

    return 0;
}
