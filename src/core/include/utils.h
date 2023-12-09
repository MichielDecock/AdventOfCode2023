#pragma once
#include <string>
#include <vector>

namespace core
{

std::vector<std::string> readFile(const char* fileName, const std::vector<char>& delimiters = {});

std::size_t sum(const std::vector<size_t>& numbers);

std::vector<size_t> extractNumbers(const std::string& string);

} // namespace core
