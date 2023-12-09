#pragma once
#include <tuple>
#include <vector>

namespace core
{

using Values = std::vector<size_t>;

std::tuple<Values, Values> readRecords(const char* fileName);

Values distances(size_t time);

size_t newRecords(const Values& distances, size_t record);

size_t ways(const Values& newRecords);

size_t ways(const char* fileName);

} // namespace core
