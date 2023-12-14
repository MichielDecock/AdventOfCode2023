#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "loop.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;
using namespace core;

MATCHER_P(matchPosition, expectedValue, "Positions don't match")
{
    return expectedValue.row == arg.row && expectedValue.column == arg.column;
}

TEST(Loop, findStart)
{
    const auto lines = readFile("tests/res/tests_loop");

    EXPECT_THAT(*findStart(lines), matchPosition(Node(2, 0)));
}

TEST(Loop, farthestDistance)
{
    auto distance = [](const char* fileName) { return std::get<0>(farthestDistance(fileName)); };

    EXPECT_EQ(8, distance("tests/res/tests_loop"));
    EXPECT_EQ(23, distance("tests/res/tests_loop_inner_tiles1"));
    EXPECT_EQ(22, distance("tests/res/tests_loop_inner_tiles2"));
    EXPECT_EQ(70, distance("tests/res/tests_loop_inner_tiles3"));
    EXPECT_EQ(80, distance("tests/res/tests_loop_inner_tiles4"));
}

TEST(Loop, innerTiles)
{
    EXPECT_EQ(1, innerTiles("tests/res/tests_loop"));
    EXPECT_EQ(4, innerTiles("tests/res/tests_loop_inner_tiles1"));
    EXPECT_EQ(4, innerTiles("tests/res/tests_loop_inner_tiles2"));
    EXPECT_EQ(8, innerTiles("tests/res/tests_loop_inner_tiles3"));
    EXPECT_EQ(10, innerTiles("tests/res/tests_loop_inner_tiles4"));
}

} // namespace gtest
