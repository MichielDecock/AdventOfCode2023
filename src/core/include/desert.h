#pragma once
#include <string>
#include <vector>

namespace core
{

using Instructions = std::vector<bool>;
using Node = size_t;
using Nodes = std::vector<Node>;

struct Path
{
    Node left = {};
    Node right = {};
};

using Paths = std::vector<Path>;

std::tuple<Instructions, Paths, Nodes, Nodes> convertInput(const char* filePath);

using Steps = unsigned long long;

Steps steps(const char* filePath);

} // namespace core
