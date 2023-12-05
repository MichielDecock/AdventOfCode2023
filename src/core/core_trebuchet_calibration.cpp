#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>

#include "include/core_trebuchet_calibration.h"

namespace
{
const char* digits = "0123456789";

std::optional<size_t> extractFrontNumber(const std::string& string)
{
    const auto map = core::textNumberMap();

    const size_t plainHitFront = string.find_first_of(digits);

    size_t      textHitFront = string.npos;
    std::string textFront;

    for (const auto& item : map)
    {
        const auto found = string.find(item.first);
        if (found == string.npos)
            continue;

        if (found < textHitFront)
        {
            textHitFront = found;
            textFront = item.first;
        }
    }

    if (std::min(plainHitFront, textHitFront) == string.npos)
        return {};

    return (plainHitFront < textHitFront) ? static_cast<size_t>(string[plainHitFront] - 48)
                                          : map.at(textFront);
}

std::optional<size_t> extractBacktNumber(const std::string& string)
{
    const auto map = core::textNumberMap();

    const size_t plainHitBack = string.find_last_of(digits);

    size_t      textHitBack = string.npos;
    std::string textBack;

    for (const auto& item : map)
    {
        const auto found = string.rfind(item.first);
        if (found == string.npos)
            continue;

        if (found > textHitBack || textHitBack == string.npos)
        {
            textHitBack = found;
            textBack = item.first;
        }
    }

    if (std::min(plainHitBack, textHitBack) == string.npos)
        return {};

    if (plainHitBack == string.npos)
        return map.at(textBack);

    if (textHitBack == string.npos)
        return static_cast<size_t>(string[plainHitBack] - 48);

    return (plainHitBack > textHitBack) ? static_cast<size_t>(string[plainHitBack] - 48)
                                        : map.at(textBack);
}

} // namespace
namespace core
{

using numberMapType = std::map<std::string, size_t>;

std::vector<std::string> readFile(const char* fileName, char delimiter)
{
    std::vector<std::string> lines;

    std::fstream fstream;
    fstream.open(std::string(CMAKE_SOURCE_DIR) + "/" + fileName);

    std::string line;
    while (std::getline(fstream, line))
    {
        if (line.empty())
            continue;

        std::stringstream sstream(line);
        std::string       partOfLine;
        while (std::getline(sstream, partOfLine, delimiter))
        {
            if (partOfLine.empty())
                continue;

            lines.push_back(partOfLine);
        }
    }

    return lines;
}

std::map<std::string, size_t> textNumberMap()
{
    const auto lines = core::readFile("res/digits", ';');

    if (lines.size() % 2 != 0)
        return {};

    std::map<std::string, size_t> map;

    for (size_t i = 0; i != lines.size(); i += 2)
    {
        map[lines[i]] = std::atoi(lines[i + 1].c_str());
    }

    return map;
}

std::vector<size_t> extractNumbers(const std::vector<std::string>& strings)
{
    const auto map = textNumberMap();

    std::vector<size_t> numbers;

    for (const auto& string : strings)
    {
        const auto frontNumber = extractFrontNumber(string);
        if (!frontNumber)
            continue;

        const auto backNumber = extractBacktNumber(string);
        if (!backNumber)
            continue;

        numbers.push_back(10 * *frontNumber + *backNumber);
    }

    return numbers;
}

std::size_t sum(const std::vector<size_t>& numbers)
{
    return std::accumulate(numbers.cbegin(), numbers.cend(), 0ul);
}

} // namespace core
