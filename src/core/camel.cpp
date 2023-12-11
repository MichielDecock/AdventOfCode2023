#include <cctype>
#include <map>
#include <numeric>

#include "camel.h"
#include "utils.h"

namespace core
{

static bool compChars(const char& a, const char& b)
{
    if (isdigit(a))
    {
        if (isdigit(b))
            return a > b;

        return false;
    }

    if (a == 'K' && b == 'A')
        return false;

    if (a == 'Q' && (b == 'A' || b == 'K'))
        return false;

    if (a == 'J' && (b == 'A' || b == 'K' || b == 'Q'))
        return false;

    if (a == 'T' && (b == 'A' || b == 'K' || b == 'Q' || b == 'J'))
        return false;

    return true;
};

static std::map<char, Weight> weights()
{
    static std::map<char, Weight> s_weights = {
        {'2', Weight::e2},
        {'3', Weight::e3},
        {'4', Weight::e4},
        {'5', Weight::e5},
        {'6', Weight::e6},
        {'7', Weight::e7},
        {'8', Weight::e8},
        {'9', Weight::e9},
        {'T', Weight::T},
        {'J', Weight::J},
        {'Q', Weight::Q},
        {'K', Weight::K},
        {'A', Weight::A},
    };
    return s_weights;
}

std::string sortHand(const std::string& cards)
{
    std::string sortedCards = cards;

    std::sort(sortedCards.begin(), sortedCards.end(), compChars);

    return sortedCards;
}

Type type(const std::string& hand)
{
    std::vector<size_t> counts;
    std::optional<char> curChar;

    const std::string sortedHand = sortHand(hand);

    for (const auto& c : sortedHand)
    {
        if (!curChar)
        {
            curChar = c;
            counts.push_back(1);
            continue;
        }

        if (curChar == c)
        {
            counts.back()++;
            continue;
        }

        curChar = c;
        counts.push_back(1);
    }

    if (counts.size() == 5)
        return highCard;

    if (counts.size() == 4)
        return onePair;

    if (counts.size() == 3)
    {
        if (std::find(counts.cbegin(), counts.cend(), 3) != counts.cend())
            return threeOfAKind;

        return twoPair;
    }

    if (counts.size() == 2)
    {
        if (std::find(counts.cbegin(), counts.cend(), 4) != counts.cend())
            return fourOfAKind;

        return fullHouse;
    }

    return fiveOfAKind;
}

Hands readHands(const char* fileName)
{
    const auto lines = readFile(fileName, {' '});

    Hands hands;

    Hand hand;

    for (size_t i = 0; i != lines.size(); ++i)
    {
        const auto& line = lines[i];

        if (line.empty())
            continue;

        if (i % 2 == 0)
            hand.combination = line;
        else
        {
            hand.score = std::stoll(line);
            hand.type = type(hand.combination);
            hand.weight = weight(hand.combination);
            hands.push_back(hand);
        }
    }

    return hands;
}

Hands sortHands(const char* fileName)
{
    const auto hands = readHands(fileName);

    std::array<Hands, 7> types;

    for (const auto& hand : hands)
    {
        types[hand.type - 1].push_back(hand);
    }

    auto comp = [](const auto& a, const auto& b) { return a.weight < b.weight; };

    for (auto& type : types)
    {
        std::sort(type.begin(), type.end(), comp);
    }

    Hands sortedHands;
    for (const auto& type : types)
        sortedHands.insert(sortedHands.end(), type.cbegin(), type.cend());

    return sortedHands;
}

unsigned long long totalWinnings(const char* fileName)
{
    const auto hands = core::sortHands(fileName);

    unsigned long long total = 0;

    for (size_t i = 0; i != hands.size(); ++i)
        total += hands[i].score * (i + 1);

    return total;
}

size_t weight(const std::string& string)
{
    size_t weight = 0;

    const size_t strSize = string.size();

    for (size_t i = 0; i != strSize; ++i)
    {
        weight += weights()[string[i]] * pow(15, strSize - 1 - i);
    }

    return weight;
}

} // namespace core
