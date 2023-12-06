#pragma once
#include <string>
#include <vector>

namespace core
{

std::vector<size_t> findGearNumbers(const std::vector<std::string>& lines);

std::vector<size_t> extractGearRatios(const std::vector<std::string>& lines);

bool isSymbol(const char& c);

} // namespace core
