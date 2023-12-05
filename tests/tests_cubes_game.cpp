#include <gtest/gtest.h>

#include "core_cubes_game.h"
#include "core_utils.h"

#include <iostream>

TEST(CubesGame, readFile)
{
    const auto lines = core::readFile("tests/res/tests_cubes_game", {':', ';', ','});

    for (const auto& line : lines)
        std::cout << line << std::endl;
}
