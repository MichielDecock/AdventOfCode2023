#pragma once
#include <string>
#include <vector>

namespace core
{

std::vector<std::string> readInput(const char* fileName);

std::vector<size_t> extractNumbers(const std::vector<std::string>& strings);

std::size_t sum(const std::vector<size_t>& numbers);

} // namespace core
