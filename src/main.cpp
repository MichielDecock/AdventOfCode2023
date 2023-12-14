#include <iostream>

#include "loop.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::innerTiles("res/loop");

    std::cout << "Result is " << res << std::endl;

    return 0;
}
