#include <iostream>

#include "scratchcard.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto scores = core::scores("res/scratchcard");

    const size_t sum = core::sum(scores);

    std::cout << "The sum is " << sum << std::endl;

    return 0;
}
