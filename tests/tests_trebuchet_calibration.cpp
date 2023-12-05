#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core_trebuchet_calibration.h"

namespace gtest
{

namespace
{

MATCHER_P(matchMap, expectedMap, "Maps are not equal")
{
    if (expectedMap.size() != arg.size())
        return false;

    return std::all_of(expectedMap.cbegin(),
                       expectedMap.cend(),
                       [&arg](const auto& item)
                       {
                           const auto found = arg.find(item.first);
                           if (found == arg.cend())
                               return false;

                           return item.second == found->second;
                       });
}

} // namespace

TEST(TrebuchetCalibration, readFile)
{
    using namespace ::testing;
    const auto lines = core::readFile("tests/res/tests_calibration_input");

    ASSERT_EQ(9u, lines.size());
    EXPECT_THAT(lines,
                ElementsAre(StrEq("two1nine"),
                            StrEq("eightwothree"),
                            StrEq("abcone2threexyz"),
                            StrEq("xtwone3four"),
                            StrEq("4nineeightseven2"),
                            StrEq("zoneight234"),
                            StrEq("7pqrstsixteen"),
                            StrEq("fiveight"),
                            StrEq("nonumbers")));
}

TEST(TrebuchetCalibration, extractNumber)
{
    using namespace ::testing;

    const auto lines = core::readFile("tests/res/tests_calibration_input");

    const auto numbers = core::extractNumbers(lines);

    ASSERT_EQ(8u, numbers.size());
    EXPECT_THAT(numbers, ElementsAre(29, 83, 13, 24, 42, 14, 76, 58));
}

TEST(TrebuchetCalibration, sum)
{
    const auto lines = core::readFile("tests/res/tests_calibration_input");

    const auto numbers = core::extractNumbers(lines);

    EXPECT_EQ(339, core::sum(numbers));
}

TEST(TrebuchetCalibration, textNumberMap)
{
    using namespace ::testing;

    using mapType = std::map<std::string, size_t>;

    const mapType map = core::textNumberMap();

    const mapType expectedMap = {
        { "zero", 0},
        {  "one", 1},
        {  "two", 2},
        {"three", 3},
        { "four", 4},
        { "five", 5},
        {  "six", 6},
        {"seven", 7},
        {"eight", 8},
        { "nine", 9}
    };

    EXPECT_THAT(expectedMap, matchMap(map));
}

} //namespace gtest
