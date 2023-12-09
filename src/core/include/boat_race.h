#pragma once
#include <tuple>
#include <vector>

namespace core
{

using Values = std::vector<size_t>;

std::tuple<Values, Values> readRecords(const char* fileName);

size_t ways(const char* fileName);

std::tuple<size_t, size_t> getLimits(size_t totalTime, size_t currentRecords);

} // namespace core
