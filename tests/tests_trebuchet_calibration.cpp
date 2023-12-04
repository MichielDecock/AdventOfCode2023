#include <gtest/gtest.h>

#include "core_trebuchet_calibration.h"

namespace gtest
{

TEST(TrebuchetCalibration, readInput)
{
    const auto lines = core::readInput("tests/res/tests_calibration_input");

    ASSERT_EQ(4u, lines.size());
    EXPECT_STREQ("1abc2", lines[0].c_str());
    EXPECT_STREQ("pqr3stu8vwx", lines[1].c_str());
    EXPECT_STREQ("a1b2c3d4e5f", lines[2].c_str());
    EXPECT_STREQ("treb7uchet", lines[3].c_str());
}

} //namespace gtest
