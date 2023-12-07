#pragma once
#include <string>
#include <vector>

namespace core
{

std::vector<std::vector<std::string>> categories(const char* fileName);

std::vector<size_t> locations(const char* fileName);

std::optional<size_t> lowestLocation(const std::vector<size_t>& locations);

} // namespace core