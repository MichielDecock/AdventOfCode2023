#include <iostream>

#include "core_cubes_game.h"
#include "core_utils.h"

int main(int argc, char** argv)
{
    const auto ids = core::powerGameIDs("res/cubes_game_input");

    const size_t sum = core::sum(ids);

    std::cout << "The cubes game ID sum is " << sum << std::endl;

    return 0;
}
