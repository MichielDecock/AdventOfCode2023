#include <sstream>
#include <string>

#include "include/scratchcard.h"
#include "include/utils.h"

#include <iostream>

namespace
{

// trim from start (in place)
inline void ltrim(std::string& s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
}

// trim from both ends (in place)
inline void trim(std::string& s)
{
    rtrim(s);
    ltrim(s);
}

} // namespace

namespace core
{

std::vector<size_t> scores(const char* fileName)
{
    const auto lines = readFile(fileName, {':', '|'});

    std::vector<size_t> scores;

    std::optional<size_t> score;
    std::vector<size_t>   winningNumbers;

    for (size_t i = 0; i != lines.size(); ++i)
    {
        auto currentLine = lines[i];
        trim(currentLine);

        if (i % 3 == 0)
        {
            if (score)
                scores.push_back(*score);

            score = 0;
        }
        else if (i % 3 == 1)
        {
            std::stringstream sstream(currentLine);
            std::string       numberString;

            winningNumbers.clear();

            while (std::getline(sstream, numberString, ' '))
            {
                if (numberString.empty())
                    continue;

                winningNumbers.push_back(std::stoi(numberString));
            }
        }
        else if (i % 3 == 2)
        {
            std::stringstream sstream(currentLine);
            std::string       numberString;

            while (std::getline(sstream, numberString, ' '))
            {
                if (numberString.empty())
                    continue;

                if (std::find(winningNumbers.cbegin(),
                              winningNumbers.cend(),
                              std::stoi(numberString)) != winningNumbers.cend())
                {
                    score = *score + 1;
                }
            }
        }
    }

    if (score)
        scores.push_back(*score);

    return scores;
}

std::vector<size_t> numberOfScratchCards(const char* fileName)
{
    const auto winningCards = scores(fileName);

    std::vector<size_t> cards(winningCards.size(), 1);

    for (size_t i = 0; i != winningCards.size(); ++i)
    {
        const size_t score = winningCards[i];
        for (size_t j = 0; j != score; ++j)
        {
            if (const size_t pos = i + 1 + j; pos < cards.size())
                cards[pos] += cards[i];
        }
    }

    return cards;
}

} // namespace core
