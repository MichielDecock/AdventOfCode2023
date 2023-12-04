#include <fstream>
#include <numeric>

#include "include/core_trebuchet_calibration.h"

namespace core
{

std::vector<std::string> readInput(const char* fileName)
{
    std::vector<std::string> lines;

    std::fstream stream;
    stream.open(std::string(CMAKE_SOURCE_DIR) + "/" + fileName);

    std::string line;
    while (std::getline(stream, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }

    return lines;
}

std::vector<size_t> extractNumbers(const std::vector<std::string>& strings)
{
    const char* digits = "0123456789";

    std::vector<size_t> numbers;

    for (const auto& string : strings)
    {
        const size_t firstHit = string.find_first_of(digits);
        const size_t lastHit = string.find_last_of(digits);
        if (firstHit == string.npos || lastHit == string.npos)
            continue;

        numbers.push_back(10 * (static_cast<size_t>(string[firstHit]) - 48) +
                          (static_cast<size_t>(string[lastHit]) - 48));
    }

    return numbers;
}

std::size_t sum(const std::vector<size_t>& numbers)
{
    return std::accumulate(numbers.cbegin(), numbers.cend(), 0ul);
}

} // namespace core
