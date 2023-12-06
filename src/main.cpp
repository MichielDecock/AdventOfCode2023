#include <iostream>

#include "cubes_game.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto ids = core::powerGameIDs("res/cubes_game");

    const size_t sum = core::sum(ids);

    std::cout << "The cubes game ID sum is " << sum << std::endl;

    return 0;
}
