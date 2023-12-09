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

    EXPECT_THAT(times, ElementsAre(7, 15, 30));
    EXPECT_THAT(distances, ElementsAre(9, 40, 200));
}

TEST(BoatRace, allDistances)
{
    const auto [times, distances] = core::readRecords("tests/res/tests_boat_race");

    core::Values dist1 = core::distances(times[0]);
    EXPECT_THAT(dist1, ElementsAre(0, 6, 10, 12, 12, 10, 6, 0));
}

TEST(BoatRace, newRecords)
{
    const auto [times, distances] = core::readRecords("tests/res/tests_boat_race");

    core::Values dist1 = core::distances(times[0]);
    const size_t records = core::newRecords(dist1, times[0]);
    EXPECT_EQ(4, records);
}

TEST(BoatRace, ways)
{
    EXPECT_EQ(288, core::ways("tests/res/tests_boat_race"));
}

} // namespace gtest
