#include <gtest/gtest.h>

#include "core_trebuchet_calibration.h"

namespace gtest
{

TEST(TrebuchetCalibration, readInput)
{
    const auto lines = core::readInput("tests/res/tests_calibration_input");

    ASSERT_EQ(5u, lines.size());
    EXPECT_STREQ("1abc2", lines[0].c_str());
    EXPECT_STREQ("pqr3stu8vwx", lines[1].c_str());
    EXPECT_STREQ("a1b2c3d4e5f", lines[2].c_str());
    EXPECT_STREQ("treb7uchet", lines[3].c_str());
}

TEST(TrebuchetCalibration, extractNumber)
{
    const auto lines = core::readInput("tests/res/tests_calibration_input");

    const auto numbers = core::extractNumbers(lines);

    ASSERT_EQ(4u, numbers.size());
    EXPECT_EQ(12, numbers[0]);
    EXPECT_EQ(38, numbers[1]);
    EXPECT_EQ(15, numbers[2]);
    EXPECT_EQ(77, numbers[3]);
}

TEST(TrebuchetCalibration, sum)
{
    const auto lines = core::readInput("tests/res/tests_calibration_input");

    const auto numbers = core::extractNumbers(lines);

    EXPECT_EQ(142, core::sum(numbers));
}

} //namespace gtest
