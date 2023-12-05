#pragma once
#include <string>
#include <vector>

namespace core
{

std::vector<std::string> readFile(const char* fileName, const std::vector<char>& delimiters = {});

} // namespace core
