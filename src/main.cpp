#include <iostream>

#include "cosmic.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::sum(core::distances("res/cosmic.txt", 1000000));

    std::cout << "Result is " << res << std::endl;

    return 0;
}
