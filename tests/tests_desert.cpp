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
    const auto [instructions, paths, starts, targets] =
        convertInput("tests/res/tests_desert_ghost");

    EXPECT_THAT(starts, ElementsAre(0, 3));
    EXPECT_THAT(targets, ElementsAre(2, 6));
    EXPECT_THAT(instructions, ElementsAre(false, true));
    EXPECT_THAT(paths,
                ElementsAre(matchPath(Path({1, 7})),
                            matchPath(Path({7, 2})),
                            matchPath(Path({1, 7})),
                            matchPath(Path({4, 7})),
                            matchPath(Path({5, 5})),
                            matchPath(Path({6, 6})),
                            matchPath(Path({4, 4})),
                            matchPath(Path({7, 7}))));
}

} // namespace gtest
