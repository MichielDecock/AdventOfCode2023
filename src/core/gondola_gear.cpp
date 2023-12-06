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

bool isSymbol(const char& c)
{
    return !isdigit(c) && (c != '.');
}

} // namespace core
