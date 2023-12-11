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
                            matchHand(Hand({"T55J5", 684, Type::fourOfAKind})),
                            matchHand(Hand({"KK677", 28, Type::twoPair})),
                            matchHand(Hand({"KTJJT", 220, Type::fourOfAKind})),
                            matchHand(Hand({"QQQJA", 483, Type::fourOfAKind}))));
}

TEST(Camel, sortHand)
{
    EXPECT_STREQ("AKQT98765432J", core::sortHand("2439TQK65A7J8").c_str());
}

TEST(Camel, type)
{
    EXPECT_EQ(Type::highCard, core::type("65432"));
    EXPECT_EQ(Type::onePair, core::type("AA432"));
    EXPECT_EQ(Type::onePair, core::type("AJ432"));
    EXPECT_EQ(Type::twoPair, core::type("43322"));
    EXPECT_EQ(Type::threeOfAKind, core::type("TTT98"));
    EXPECT_EQ(Type::threeOfAKind, core::type("TJ9J8"));
    EXPECT_EQ(Type::threeOfAKind, core::type("T99J8"));
    EXPECT_EQ(Type::fullHouse, core::type("33322"));
    EXPECT_EQ(Type::fullHouse, core::type("33J22"));
    EXPECT_EQ(Type::fourOfAKind, core::type("AAAA4"));
    EXPECT_EQ(Type::fourOfAKind, core::type("AJAA4"));
    EXPECT_EQ(Type::fourOfAKind, core::type("AJAJ4"));
    EXPECT_EQ(Type::fourOfAKind, core::type("JJAJ4"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AAAAA"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AAAAJ"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AAAJJ"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AAJJJ"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("AJJJJ"));
    EXPECT_EQ(Type::fiveOfAKind, core::type("JJJJJ"));
}

TEST(Camel, sortHands)
{
    const auto hands = core::sortHands("tests/res/tests_camel");

    EXPECT_THAT(hands,
                ElementsAre(matchHand(Hand({"32T3K", 765, Type::onePair})),
                            matchHand(Hand({"KK677", 28, Type::twoPair})),
                            matchHand(Hand({"T55J5", 684, Type::fourOfAKind})),
                            matchHand(Hand({"QQQJA", 483, Type::fourOfAKind})),
                            matchHand(Hand({"KTJJT", 220, Type::fourOfAKind}))));
}

TEST(Camel, totalWinnings)
{
    EXPECT_EQ(5905, core::totalWinnings("tests/res/tests_camel"));
}

TEST(Camel, weight)
{
    const core::Hands hands = core::readHands("tests/res/tests_camel");
    EXPECT_EQ(12 + 3 * 15 + 10 * 225 + 2 * 3375 + 3 * 50625, hands[0].weight);
    EXPECT_EQ(10 + 1 * 15 + 1 * 225 + 10 * 3375 + 12 * 50625, hands[3].weight);
}

} // namespace gtest