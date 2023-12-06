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

    EXPECT_THAT(scores, ElementsAre(4, 2, 2, 1, 0, 1));
}

TEST(ScratchCard, sum)
{
    const auto scores = core::scores("tests/res/tests_scratchcard");
    EXPECT_EQ(10, core::sum(scores));

    const auto cards = core::numberOfScratchCards("tests/res/tests_scratchcard");
    EXPECT_EQ(30, core::sum(cards));
}

TEST(ScratchCard, numberOfScratchCards)
{
    using namespace ::testing;

    const auto cards = core::numberOfScratchCards("tests/res/tests_scratchcard");

    EXPECT_THAT(cards, ElementsAre(1, 2, 4, 8, 14, 1));
}

} // namespace gtest
