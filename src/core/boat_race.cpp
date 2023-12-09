#include "boat_race.h"
#include "utils.h"

namespace core
{

std::tuple<Values, Values> readRecords(const char* fileName)
{
    const auto lines = readFile(fileName);

    return std::make_tuple(extractNumbers(lines.front()), extractNumbers(lines.back()));
}

size_t ways(const char* fileName)
{
    const auto [times, distances] = readRecords(fileName);

    const auto [min, max] = core::getLimits(times.front(), distances.front());

    return max - min + 1;
}

std::tuple<size_t, size_t> getLimits(size_t totalTime, size_t currentRecord)
{
    const unsigned long long D = std::sqrt(totalTime * totalTime - 4 * currentRecord);

    const size_t min = std::ceil(0.5 * (totalTime - D));
    const size_t max = std::floor(0.5 * (totalTime + D));

    return std::make_tuple(min, max);
}

} // namespace core
