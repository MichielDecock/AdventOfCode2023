#include <sstream>

#include "include/seeds.h"
#include "include/utils.h"

namespace
{

std::vector<size_t> extractNumbers(const std::string& string)
{
    std::stringstream ss(string);
    std::string       number;

    std::vector<size_t> numbers;

    while (std::getline(ss, number, ' '))
    {
        if (number.empty())
            continue;

        numbers.push_back(std::stoll(number));
    }

    return numbers;
}

std::vector<size_t> getSeeds(const std::string& string)
{
    return extractNumbers(string);
}

std::vector<std::vector<size_t>> getMap(const std::vector<std::string>& strings)
{
    std::vector<std::vector<size_t>> map;

    for (const auto& string : strings)
    {
        auto numbers = extractNumbers(string);
        map.push_back(numbers);
    }

    return map;
}

std::optional<size_t> mapped(const std::vector<std::vector<size_t>>& map, size_t seed)
{
    for (const auto& line : map)
    {
        const size_t destBegin = line[0];
        const size_t sourceBegin = line[1];
        const size_t range = line[2];

        const size_t delta = seed - sourceBegin;

        if (delta >= 0 && delta < range)
            return destBegin + delta;
    }

    return {};
}

std::vector<size_t> useMap(const std::vector<std::vector<size_t>>& map,
                           const std::vector<size_t>&              seeds)
{
    std::vector<size_t> mappedSeeds = seeds;

    for (auto& seed : mappedSeeds)
    {
        if (const auto mappedValue = mapped(map, seed))
            seed = *mappedValue;
    }

    return mappedSeeds;
}
} // namespace

namespace core
{

std::vector<std::vector<std::string>> categories(const char* fileName)
{
    const auto lines = readFile(fileName);

    std::vector<std::vector<std::string>> categories;
    std::vector<std::string>              category;

    for (const auto& line : lines)
    {
        if (line != "|")
        {
            category.push_back(line);
        }
        else
        {
            categories.push_back(category);
            category.clear();
        }
    }

    return categories;
}

std::vector<size_t> locations(const char* fileName)
{
    auto cats = categories(fileName);

    std::vector<size_t> seeds = getSeeds(cats.front().front());

    for (size_t category = 1; category != cats.size(); ++category)
    {
        const auto map = getMap(cats[category]);
        seeds = useMap(map, seeds);
    }

    return seeds;
}

std::optional<size_t> lowestLocation(const std::vector<size_t>& locations)
{
    auto lowest = std::min_element(locations.cbegin(), locations.cend());

    if (lowest != locations.cend())
        return *lowest;

    return {};
}

} // namespace core
