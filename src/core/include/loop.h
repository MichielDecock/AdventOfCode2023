#pragma once
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace core
{

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node
{
    Node() = default;
    Node(size_t row, size_t column);

    size_t row = {};
    size_t column = {};

    size_t distance = -1; // init with max size_t, represents "infinity"

    std::vector<NodePtr> neighbors;
};

NodePtr findStart(const std::vector<std::string>& lines);

using PotentialStart = std::tuple<NodePtr, NodePtr>;
std::vector<PotentialStart> potentialStarts(const std::vector<std::string>& lines);

struct Comparator
{
    bool operator()(const NodePtr& node1, const NodePtr& node2) const;
};
using Graph = std::set<NodePtr, Comparator>;

Graph cloneGraph(const Graph& graph);

Graph convertToGraph(const std::vector<std::string>& lines);

std::tuple<size_t, NodePtr> farthestDistance(const char* fileName);

size_t innerTiles(const char* fileName);

Graph getLoop(const NodePtr& endNode);

struct Coords
{
    Coords(size_t row, size_t column)
        : row(row)
        , column(column)
    {
    }

    size_t row = {};
    size_t column = {};
};

} // namespace core
