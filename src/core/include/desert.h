#pragma once
#include <string>
#include <vector>

namespace core
{

using Instructions = std::vector<bool>;
using Node = size_t;

struct Path
{
    Node left = {};
    Node right = {};
};

using Paths = std::vector<Path>;

std::tuple<Instructions, Paths, Node, Node> convertInput(const char* filePath);

using Steps = unsigned long long;

Steps steps(const char* filePath);

} // namespace core
