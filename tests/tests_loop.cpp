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
    EXPECT_EQ(8, farthestDistance("tests/res/tests_loop"));
}

} // namespace gtest
