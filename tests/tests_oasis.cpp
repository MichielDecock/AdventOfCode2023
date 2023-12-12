#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "oasis.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;
using namespace core;

TEST(Oasis, extrapolatedValues)
{
    const auto values = extrapolatedValues("tests/res/tests_oasis");
    EXPECT_THAT(values, ElementsAre(-3, 0, 5));
}

TEST(Oasis, sum)
{
    EXPECT_EQ(2, sum(extrapolatedValues("tests/res/tests_oasis")));
}

} // namespace gtest
