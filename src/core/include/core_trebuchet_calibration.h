#pragma once
#include <map>
#include <string>
#include <vector>

namespace core
{

std::vector<std::string> readFile(const char* fileName, char delimiter = {});

std::map<std::string, size_t> textNumberMap();

std::vector<size_t> extractNumbers(const std::vector<std::string>& strings);

std::size_t sum(const std::vector<size_t>& numbers);

} // namespace core
