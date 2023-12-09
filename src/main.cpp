#include <iostream>

#include "boat_race.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::ways("res/boat_race");

    std::cout << "Result is " << res << std::endl;

    return 0;
}
