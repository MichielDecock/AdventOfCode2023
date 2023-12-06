#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "gondola_gear.h"
#include "utils.h"

namespace gtest
{

TEST(GondolaGear, findGearNumbers)
{
    using namespace ::testing;

    const auto lines = core::readFile("tests/res/tests_gondola_gear");
    const auto numbers = core::findGearNumbers(lines);

    EXPECT_THAT(numbers, ElementsAre(467, 35, 633, 617, 592, 755, 664, 598, 99));
}

TEST(GondolaGear, sum)
{
    const auto lines = core::readFile("tests/res/tests_gondola_gear");

    const auto numbers = core::findGearNumbers(lines);
    EXPECT_EQ(4460, core::sum(numbers));

    const auto ratios = core::extractGearRatios(lines);
    EXPECT_EQ(467835, core::sum(ratios));
}

TEST(GondolaGear, isSymbol)
{
    EXPECT_FALSE(core::isSymbol('0'));
    EXPECT_FALSE(core::isSymbol('9'));
    EXPECT_FALSE(core::isSymbol('.'));
    EXPECT_TRUE(core::isSymbol('a'));
    EXPECT_TRUE(core::isSymbol('*'));
    EXPECT_TRUE(core::isSymbol('#'));
}

TEST(GondolaGear, extractGearRatios)
{
    using namespace ::testing;

    const auto lines = core::readFile("tests/res/tests_gondola_gear");
    const auto ratios = core::extractGearRatios(lines);

    EXPECT_THAT(ratios, ElementsAre(16345, 451490));
}

} // namespace gtest