#include "boat_race.h"
#include "utils.h"

namespace core
{

std::tuple<Values, Values> readRecords(const char* fileName)
{
    const auto lines = readFile(fileName);

    return std::make_tuple(extractNumbers(lines.front()), extractNumbers(lines.back()));
}

Values distances(size_t time)
{
    Values out;

    for (size_t t = 0; t <= time; ++t)
    {
        const auto speed = t;
        const auto distance = (time - t) * speed;
        out.push_back(distance);
    }

    return out;
}

size_t newRecords(const Values& distances, size_t record)
{
    size_t records = {};

    for (const auto& distance : distances)
    {
        if (distance > record)
            records++;
    }

    return records;
}

size_t ways(const Values& newRecords)
{
    size_t ways = 1;

    for (const auto& numberRecords : newRecords)
    {
        ways *= numberRecords;
    }

    return ways;
}

size_t ways(const char* fileName)
{
    const auto [times, distances] = readRecords(fileName);

    size_t ways = 1;

    for (size_t i = 0; i != times.size(); ++i)
    {
        ways *= core::newRecords(core::distances(times[i]), distances[i]);
    }

    return ways;
}

} // namespace core
