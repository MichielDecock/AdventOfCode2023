#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "boat_race.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;

TEST(BoatRace, readRecords)
{
    const auto [times, distances] = core::readRecords("tests/res/tests_boat_race");

    EXPECT_THAT(times, ElementsAre(71530));
    EXPECT_THAT(distances, ElementsAre(940200));
}

TEST(BoatRace, getLimits)
{
    const auto [times, distances] = core::readRecords("tests/res/tests_boat_race");

    const auto [min, max] = core::getLimits(times.front(), distances.front());

    EXPECT_EQ(14, min);
    EXPECT_EQ(71516, max);
}

TEST(BoatRace, ways)
{
    const auto ways = core::ways("tests/res/tests_boat_race");

    EXPECT_EQ(71503, ways);
}

} // namespace gtest
