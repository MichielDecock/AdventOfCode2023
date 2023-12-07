#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "seeds.h"
#include "utils.h"

namespace gtest
{

TEST(Seeds, location)
{
    using namespace ::testing;

    const auto locations = core::locations("tests/res/tests_seeds");

    EXPECT_THAT(locations, ElementsAre(82, 43, 86, 35));
}

TEST(Seeds, lowestLocation)
{
    using namespace ::testing;

    const auto locations = core::locations("tests/res/tests_seeds");

    const auto lowest = core::lowestLocation(locations);

    EXPECT_EQ(35, *lowest);
}

} // namespace gtest
