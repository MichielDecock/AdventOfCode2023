#include <cctype>

#include "include/gondola_gear.h"

namespace
{

bool findSymbol(const std::vector<std::string>& lines,
                size_t                          startPos,
                size_t                          endPos,
                size_t                          currentLineIndex)
{
    std::string currentLine = lines[currentLineIndex];

    std::optional<std::string> previousLine;
    if (currentLineIndex > 0)
        previousLine = lines[currentLineIndex - 1];

    std::optional<std::string> nextLine;
    if (currentLineIndex < lines.size() - 1)
        nextLine = lines[currentLineIndex + 1];

    if (startPos > 0)
    {
        if (previousLine && core::isSymbol((*previousLine)[startPos - 1]))
            return true;

        if (core::isSymbol((currentLine)[startPos - 1]))
            return true;

        if (nextLine && core::isSymbol((*nextLine)[startPos - 1]))
            return true;
    }

    if (endPos < currentLine.size() - 1)
    {
        if (previousLine && core::isSymbol((*previousLine)[endPos + 1]))
            return true;

        if (core::isSymbol((currentLine)[endPos + 1]))
            return true;

        if (nextLine && core::isSymbol((*nextLine)[endPos + 1]))
            return true;
    }

    for (size_t i = startPos; i != (endPos + 1); ++i)
    {
        if (previousLine && core::isSymbol((*previousLine)[i]))
            return true;

        if (nextLine && core::isSymbol((*nextLine)[i]))
            return true;
    }

    return {};
}

bool isGearSymbol(const char& c)
{
    return c == '*';
}

size_t findNumber(const std::string& line, size_t pos)
{
    std::string numberString;
    numberString += line[pos];

    if (pos > 0)
    {
        for (size_t i = pos - 1; i != -1; --i)
        {
            if (!isdigit(line[i]))
                break;

            numberString = line[i] + numberString;
        }
    }

    if (pos < line.size() - 1)
    {
        for (size_t i = pos + 1; i != line.size(); ++i)
        {
            if (!isdigit(line[i]))
                break;

            numberString += line[i];
        }
    }

    return std::stoi(numberString);
}

std::optional<size_t>
findRatio(const std::vector<std::string>& lines, size_t pos, size_t currentLineIndex)
{
    std::string currentLine = lines[currentLineIndex];

    std::vector<std::pair<size_t, size_t>> numberPositions;

    auto stop = [&numberPositions]() { return numberPositions.size() == 2; };

    for (size_t i = std::max(static_cast<int>(currentLineIndex) - 1, 0);
         i != std::min(currentLineIndex + 1, lines.size() - 1) + 1;
         ++i)
    {
        bool newNumber = true;

        for (size_t j = std::max(static_cast<int>(pos) - 1, 0);
             j != std::min(pos + 1, currentLine.size() - 1) + 1;
             ++j)
        {
            if (!isdigit(lines[i][j]))
            {
                newNumber = true;
                continue;
            }

            if (!newNumber)
                continue;

            if (stop())
                return {};

            numberPositions.push_back(std::make_pair(i, j));
            newNumber = false;
        }
    }

    if (numberPositions.size() != 2)
        return {};

    const size_t firstNumber =
        findNumber(lines[numberPositions.front().first], numberPositions.front().second);
    const size_t secondNumber =
        findNumber(lines[numberPositions.back().first], numberPositions.back().second);

    return firstNumber * secondNumber;
}

} // namespace

namespace core
{

std::vector<size_t> findGearNumbers(const std::vector<std::string>& lines)
{
    std::vector<size_t> numbers;

    for (size_t i = 0; i != lines.size(); ++i)
    {
        const std::string line = lines[i];

        std::string numberString;
        size_t      startPos = 0;
        size_t      endPos = 0;

        for (size_t j = 0; j != line.size(); ++j)
        {
            if (isdigit(line[j]))
            {
                if (numberString.empty())
                    startPos = j;

                numberString += line[j];
            }
            else if (!numberString.empty())
            {
                endPos = j - 1;

                if (findSymbol(lines, startPos, endPos, i))
                    numbers.push_back(std::stoi(numberString));

                numberString = "";
            }
        }

        if (!numberString.empty())
        {
            endPos = line.size() - 1;

            if (findSymbol(lines, startPos, endPos, i))
                numbers.push_back(std::stoi(numberString));
        }
    }

    return numbers;
}

std::vector<size_t> extractGearRatios(const std::vector<std::string>& lines)
{
    std::vector<size_t> ratios;

    for (size_t i = 0; i != lines.size(); ++i)
    {
        const std::string line = lines[i];

        for (size_t j = 0; j != line.size(); ++j)
        {
            if (!isGearSymbol(line[j]))
                continue;

            if (const auto ratio = findRatio(lines, j, i))
                ratios.push_back(*ratio);
        }
    }

    return ratios;
}

bool isSymbol(const char& c)
{
    return !isdigit(c) && (c != '.');
}

} // namespace core
