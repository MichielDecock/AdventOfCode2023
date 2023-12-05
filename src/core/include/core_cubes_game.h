#pragma once
#include <vector>

namespace core
{

std::vector<size_t>
validGameIDs(const char* fileName, size_t maxRed, size_t maxGreen, size_t maxBlue);

std::vector<size_t> powerGameIDs(const char* fileName);

} // namespace core
