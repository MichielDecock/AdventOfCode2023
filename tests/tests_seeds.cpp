#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "seeds.h"
#include "utils.h"

namespace gtest
{

using Seed = core::Seed;
using Map = std::vector<size_t>;

namespace
{

MATCHER_P(matchMapping, expectedMapping, "Mappings are not equal")
{
    for (size_t i = 0; i != expectedMapping.size(); ++i)
    {
        if (expectedMapping[i] != arg[i])
            return false;
    }

    return true;
}

MATCHER_P(matchSeed, expectedSeed, "Seeds are not equal")
{
    return expectedSeed.first == arg.first && expectedSeed.second == arg.second;
}

} // namespace

TEST(Seeds, useMap)
{
    using namespace ::testing;

    auto cats = core::categories("tests/res/tests_seeds_usemap");

    Seed seed = core::getSeeds(cats.front().front()).front();

    EXPECT_THAT(Seed(4u, 5u), matchSeed(seed));

    const auto map = core::getMap(cats[1]);

    Map expectedMap = {4u, 1u, 2u};
    EXPECT_THAT(expectedMap, matchMapping(map[0]));
    expectedMap = {4u, 2u, 4u};
    EXPECT_THAT(expectedMap, matchMapping(map[1]));
    expectedMap = {4u, 3u, 10u};
    EXPECT_THAT(expectedMap, matchMapping(map[2]));
    expectedMap = {4u, 6u, 2u};
    EXPECT_THAT(expectedMap, matchMapping(map[3]));
    expectedMap = {4u, 6u, 4u};
    EXPECT_THAT(expectedMap, matchMapping(map[4]));
    expectedMap = {4u, 10u, 3u};
    EXPECT_THAT(expectedMap, matchMapping(map[5]));

    auto mappedSeeds = core::useMap({map[0]}, {seed});
    EXPECT_THAT(Seed(4u, 5u), matchSeed(mappedSeeds[0]));

    mappedSeeds = core::useMap({map[1]}, {seed});
    EXPECT_THAT(Seed(6u, 2u), matchSeed(mappedSeeds[0]));
    EXPECT_THAT(Seed(6u, 3u), matchSeed(mappedSeeds[1]));

    mappedSeeds = core::useMap({map[2]}, {seed});
    EXPECT_THAT(Seed(5u, 5u), matchSeed(mappedSeeds[0]));

    mappedSeeds = core::useMap({map[3]}, {seed});
    EXPECT_THAT(Seed(4u, 2u), matchSeed(mappedSeeds[0]));
    EXPECT_THAT(Seed(4u, 2u), matchSeed(mappedSeeds[1]));
    EXPECT_THAT(Seed(8u, 1u), matchSeed(mappedSeeds[2]));

    mappedSeeds = core::useMap({map[4]}, {seed});
    EXPECT_THAT(Seed(4u, 3u), matchSeed(mappedSeeds[0]));
    EXPECT_THAT(Seed(4u, 2u), matchSeed(mappedSeeds[1]));

    mappedSeeds = core::useMap({map[5]}, {seed});
    EXPECT_THAT(Seed(4u, 5u), matchSeed(mappedSeeds[0]));
}

TEST(Seeds, location)
{
    using namespace ::testing;

    const auto locations = core::locations("tests/res/tests_seeds_small");

    EXPECT_THAT(Seed(60u, 1u), matchSeed(locations[0]));
    EXPECT_THAT(Seed(82u, 3u), matchSeed(locations[1]));
    EXPECT_THAT(Seed(46u, 10u), matchSeed(locations[2]));
}

TEST(Seeds, lowestLocation)
{
    using namespace ::testing;

    const auto locations = core::locations("tests/res/tests_seeds");

    const auto lowest = core::lowestLocation(locations);

    EXPECT_EQ(46, *lowest);
}

} // namespace gtest
