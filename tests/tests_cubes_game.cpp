#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core_cubes_game.h"
#include "core_utils.h"

TEST(CubesGame, validGameIDs)
{
    using namespace ::testing;

    const auto ids = core::validGameIDs("tests/res/tests_cubes_game", 12, 13, 14);

    EXPECT_EQ(3u, ids.size());
    EXPECT_THAT(ids, ElementsAre(1u, 2u, 5u));
}

TEST(CubesGame, sum)
{
    const auto ids = core::validGameIDs("tests/res/tests_cubes_game", 12, 13, 14);

    EXPECT_EQ(8u, core::sum(ids));
}
