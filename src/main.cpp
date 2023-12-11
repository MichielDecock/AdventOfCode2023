#include <iostream>

#include "camel.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::totalWinnings("res/camel");

    std::cout << "Result is " << res << std::endl;

    return 0;
}
