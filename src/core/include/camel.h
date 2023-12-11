#pragma once
#include <string>
#include <vector>

namespace core
{

enum Type
{
    highCard = 1,
    onePair,
    twoPair,
    threeOfAKind,
    fullHouse,
    fourOfAKind,
    fiveOfAKind
};

enum Weight
{
    e2 = 1,
    e3,
    e4,
    e5,
    e6,
    e7,
    e8,
    e9,
    T,
    J,
    Q,
    K,
    A
};

struct Hand
{
    std::string combination;
    size_t      score = 0;
    Type        type;
    size_t      weight = 0;
};
using Hands = std::vector<Hand>;

std::string sortHand(const std::string& cards);

Type type(const std::string& cards);

Hands readHands(const char* fileName);

Hands sortHands(const char* fileName);

unsigned long long totalWinnings(const char* fileName);

size_t weight(const std::string& string);

} // namespace core