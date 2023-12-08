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

bool findFrontMatch(std::vector<std::pair<core::Seed, bool>>& mappedSeeds,
                    const core::Map&                          mapping,
                    size_t                                    iSeed)
{
    if (mappedSeeds[iSeed].second)
        return true;

    const size_t destStart = mapping[0];
    const size_t sourceStart = mapping[1];
    const size_t range = mapping[2];

    const core::Seed seed = mappedSeeds[iSeed].first;

    const long long signedDelta = seed.first - sourceStart;
    if (signedDelta < 0)
        return false;

    const auto delta = static_cast<size_t>(signedDelta);
    if (delta >= range)
        return true;

    const size_t     mappedItems = std::min(seed.second, range - delta);
    const auto mappedSeed = std::make_pair(std::make_pair(destStart + delta, mappedItems), true);

    const size_t post = seed.second - mappedItems;
    if (post > 0)
        mappedSeeds.push_back(
            std::make_pair(std::make_pair(seed.first + mappedItems, post), false));

    mappedSeeds[iSeed] = mappedSeed;

    return true;
}

void findBackMatch(std::vector<std::pair<core::Seed, bool>>& mappedSeeds,
                   const core::Map&                          mapping,
                   size_t                                    iSeed)
{
    const size_t destStart = mapping[0];
    const size_t sourceStart = mapping[1];
    const size_t range = mapping[2];

    const core::Seed seed = mappedSeeds[iSeed].first;

    const size_t seedBack = seed.first + seed.second - 1;
    const size_t destBack = destStart + range - 1;

    const long long signedDelta = seedBack - sourceStart;
    if (signedDelta < 0)
        return;

    const auto delta = static_cast<size_t>(signedDelta);

    const size_t mappedItems = std::min(delta + 1, range);

    const size_t pre = seed.second - delta - 1;
    if (pre > 0)
        mappedSeeds.push_back(std::make_pair(std::make_pair(seed.first, pre), false));

    const size_t post = seed.second - pre - mappedItems;
    if (post > 0)
        mappedSeeds.push_back(
            std::make_pair(std::make_pair(seed.first + pre + mappedItems, post), false));

    if (mappedItems)
        mappedSeeds[iSeed] = std::make_pair(std::make_pair(destStart, mappedItems), true);
}

void useMapping(std::vector<std::pair<core::Seed, bool>>& mappedSeeds,
                const core::Map&                          mapping,
                size_t                                    iSeed)
{
    if (!findFrontMatch(mappedSeeds, mapping, iSeed))
        findBackMatch(mappedSeeds, mapping, iSeed);
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

std::vector<Seed> locations(const char* fileName)
{
    auto cats = categories(fileName);

    std::vector<Seed> seeds = getSeeds(cats.front().front());

    for (size_t category = 1; category != cats.size(); ++category)
    {
        const auto map = getMap(cats[category]);
        seeds = useMap(map, seeds);
    }

    return seeds;
}

std::optional<size_t> lowestLocation(const std::vector<Seed>& locations)
{
    auto lowest = std::min_element(locations.cbegin(),
                                   locations.cend(),
                                   [](const auto& a, const auto& b) { return a.first < b.first; });

    if (lowest != locations.cend())
        return lowest->first;

    return {};
}

std::vector<Seed> getSeeds(const std::string& string)
{
    std::stringstream ss(string);
    std::string       number;

    std::vector<Seed> seeds;

    std::optional<size_t> start;

    while (std::getline(ss, number, ' '))
    {
        if (number.empty())
            continue;

        if (!start)
        {
            start = std::stoll(number);
            continue;
        }

        seeds.push_back(std::make_pair(*start, std::stoll(number)));

        start = std::nullopt;
    }

    return seeds;
}

std::vector<Map> getMap(const std::vector<std::string>& strings)
{
    std::vector<std::vector<size_t>> map;

    for (const auto& string : strings)
    {
        auto numbers = extractNumbers(string);
        map.push_back(numbers);
    }

    return map;
}

std::vector<Seed> useMap(const std::vector<std::vector<size_t>>& map,
                         const std::vector<Seed>&                seeds)
{
    std::vector<std::pair<Seed, bool>> mappedSeeds;
    for (const auto& seed : seeds)
    {
        mappedSeeds.push_back(std::make_pair(seed, false));
    }

    for (const auto& mapping : map)
    {
        const size_t seedsCount = mappedSeeds.size();
        for (size_t iSeed = 0; iSeed != seedsCount; ++iSeed)
            useMapping(mappedSeeds, mapping, iSeed);
    }

    std::vector<Seed> output;
    for (const auto& seed : mappedSeeds)
    {
        output.push_back(seed.first);
    }

    return output;
}

} // namespace core
