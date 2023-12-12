#include <numeric>
#include <sstream>

#include "oasis.h"
#include "utils.h"

namespace core
{

static Value extrapolate(const Values& values)
{
    auto allZeroes = [](const Values& v) {
        return std::find_if(v.cbegin(), v.cend(), [](const auto& el) { return el != 0; }) ==
               v.cend();
    };

    std::vector<Values> diffs = {values};

    while (!allZeroes(diffs.back()))
    {
        const auto& lastDiff = diffs.back();
        const auto  count = lastDiff.size();

        Values diff;

        for (size_t i = 0; i + 1 < count; ++i)
            diff.push_back(lastDiff[i + 1] - lastDiff[i]);

        diffs.push_back(diff);
    }

    Value extrapol = 0;

    for (auto it = diffs.rbegin(); it != diffs.rend(); ++it)
    {
        extrapol = it->front() - extrapol;
    }

    return extrapol;
}

static Values extractUnsignedNumbers(const std::string& string)
{
    std::stringstream ss(string);
    std::string       number;

    Values numbers;

    while (std::getline(ss, number, ' '))
    {
        if (number.empty())
            continue;

        numbers.push_back(std::stoll(number));
    }

    return numbers;
}

Values extrapolatedValues(const char* fileName)
{
    const auto& lines = readFile(fileName);

    std::vector<Values> values;
    for (const auto& line : lines)
        values.push_back(extractUnsignedNumbers(line));

    Values res;
    for (const auto& value : values)
        res.push_back(extrapolate(value));

    return res;
}

Value sum(const Values& numbers)
{
    return std::accumulate(numbers.cbegin(), numbers.cend(), 0ll);
}

} // namespace core
