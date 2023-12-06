#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "scratchcard.h"
#include "utils.h"

namespace gtest
{

TEST(ScratchCard, winningNumbers)
{
    using namespace ::testing;

    const auto scores = core::scores("tests/res/tests_scratchcard");

    EXPECT_THAT(scores, ElementsAre(8, 2, 2, 1, 0, 0));
}

TEST(ScratchCard, sum)
{
    const auto scores = core::scores("tests/res/tests_scratchcard");

    EXPECT_EQ(13, core::sum(scores));
}

} // namespace gtest
