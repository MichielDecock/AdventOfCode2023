#include <iostream>

#include "oasis.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::sum(core::extrapolatedValues("res/oasis"));

    std::cout << "Result is " << res << std::endl;

    return 0;
}
