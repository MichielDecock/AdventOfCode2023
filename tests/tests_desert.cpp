#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "desert.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;
using namespace core;

MATCHER_P(matchPath, expected, "Paths are not equal")
{
    return expected.left == arg.left && expected.right == arg.right;
}

TEST(Desert, convertInput)
{
    const auto [instructions, paths, start, target] = convertInput("tests/res/tests_desert");

    EXPECT_EQ(0, start);
    EXPECT_EQ(2, target);
    EXPECT_THAT(Instructions({false, false, true}), instructions);
    EXPECT_THAT(
        paths,
        ElementsAre(matchPath(Path({1, 1})), matchPath(Path({0, 2})), matchPath(Path({2, 2}))));
}

TEST(Desert, steps)
{
    EXPECT_EQ(6, steps("tests/res/tests_desert"));
}

} // namespace gtest
