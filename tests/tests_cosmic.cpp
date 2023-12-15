#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cosmic.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;
using namespace core;

MATCHER_P(matchPos, expectedValue, "Positions don't match")
{
    return arg.x == expectedValue.x && arg.y == expectedValue.y;
}

TEST(Cosmic, getGalaxies)
{
    const auto lines = readFile("tests/res/tests_cosmic");

    EXPECT_THAT(getGalaxies(lines),
                ElementsAre(matchPos(Position(0, 3)),
                            matchPos(Position(1, 7)),
                            matchPos(Position(2, 0)),
                            matchPos(Position(4, 6)),
                            matchPos(Position(5, 1)),
                            matchPos(Position(6, 9)),
                            matchPos(Position(8, 7)),
                            matchPos(Position(9, 0)),
                            matchPos(Position(9, 4))));
}

TEST(Cosmic, expandSpace)
{
    const Positions galaxies = expandSpace("tests/res/tests_cosmic");

    EXPECT_THAT(galaxies,
                ElementsAre(matchPos(Position(0, 4)),
                            matchPos(Position(1, 9)),
                            matchPos(Position(2, 0)),
                            matchPos(Position(5, 8)),
                            matchPos(Position(6, 1)),
                            matchPos(Position(7, 12)),
                            matchPos(Position(10, 9)),
                            matchPos(Position(11, 0)),
                            matchPos(Position(11, 5))));
}

TEST(Cosmic, distances)
{
    EXPECT_EQ(374, sum(distances("tests/res/tests_cosmic")));
}

} // namespace gtest
