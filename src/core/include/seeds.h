#pragma once
#include <string>
#include <vector>

namespace core
{

using Seed = std::pair<size_t, size_t>;
using Map = std::vector<size_t>;

std::vector<std::vector<std::string>> categories(const char* fileName);

std::vector<Seed> locations(const char* fileName);

std::optional<size_t> lowestLocation(const std::vector<Seed>& locations);

std::vector<Seed> getSeeds(const std::string& string);

std::vector<Map> getMap(const std::vector<std::string>& strings);

std::vector<Seed> useMap(const std::vector<std::vector<size_t>>& map,
                         const std::vector<Seed>&                seeds);

} // namespace core