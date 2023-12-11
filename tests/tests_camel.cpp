#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "camel.h"
#include "utils.h"

namespace gtest
{

using namespace ::testing;
using namespace core;

MATCHER_P(matchHand, expectedHand, "Hands are not equal")
{
    return expectedHand.combination == arg.combination && expectedHand.score == arg.score &&
           expectedHand.type == arg.type;
}

TEST(Camel, readHands)
{
    const core::Hands hands = core::readHands("tests/res/tests_camel");
    EXPECT_THAT(hands,
                ElementsAre(matchHand(Hand({"32T3K", 765, Type::onePair})),
                            matchHand(Hand({"T55J5", 684, Type::threeOfAKind})),
                            matchHand(Hand({"KK677", 28, Type::twoPair})),
                            matchHand(Hand({"KTJJT", 220, Type::twoPair})),
                            matchHand(Hand({"QQQJA", 483, Type::threeOfAKind}))));
}

TEST(Camel, sortHand)
{
    EXPECT_STREQ("AKQJT98765432", core::sortHand("2439TQK65A7J8").c_str());
}

TEST(Camel, type)
{
    EXPECT_EQ(Type::highCard, core::type("65432"));
    EXPECT_EQ(Type::onePair, core::type("AA432"));
    EXPECT_EQ(Type::twoPair, core::type("43322"));
    EXPECT_EQ(Type::threeOfAKind, core::type("TTT98"));
    EXPECT_EQ(Type::fullHouse, core::type("33322"));
    EXPECT_EQ(Type::fourOfAKind, core::type("AAAA4"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AAAAA"));
}

TEST(Camel, sortHands)
{
    const auto hands = core::sortHands("tests/res/tests_camel");

    EXPECT_THAT(hands,
                ElementsAre(matchHand(Hand({"32T3K", 765, Type::onePair})),
                            matchHand(Hand({"KTJJT", 220, Type::twoPair})),
                            matchHand(Hand({"KK677", 28, Type::twoPair})),
                            matchHand(Hand({"T55J5", 684, Type::threeOfAKind})),
                            matchHand(Hand({"QQQJA", 483, Type::threeOfAKind}))));
}

TEST(Camel, totalWinnings)
{
    EXPECT_EQ(6440, core::totalWinnings("tests/res/tests_camel"));
}

TEST(Camel, weight)
{
    const core::Hands hands = core::readHands("tests/res/tests_camel");
    EXPECT_EQ(12 + 2 * 15 + 9 * 225 + 3375 + 2 * 50625, hands[0].weight);
}

} // namespace gtest