#include <algorithm>

#include "loop.h"
#include "utils.h"

namespace core
{

static inline bool isDot(const char& c)
{
    return c == '.';
}

static inline bool isStart(const char& c)
{
    return c == 'S';
}

static bool operator==(const Coords& co1, const Coords& co2)
{
    return co1.row == co2.row && co1.column == co2.column;
}

static bool
hasNorthNeighbor(size_t row, size_t col, const std::vector<std::string>& lines, const char& c)
{
    if (row == 0)
        return false;

    const auto& co = lines[row - 1][col];

    return (c == '|' || c == 'L' || c == 'J') && (co == '|' || co == 'F' || co == '7');
}

static bool
hasEastNeighbor(size_t row, size_t col, const std::vector<std::string>& lines, const char& c)
{
    const auto columns = lines.front().size();

    if (col == columns - 1)
        return false;

    const auto& co = lines[row][col + 1];

    return (c == '-' || c == 'F' || c == 'L') && (co == '-' || co == '7' || co == 'J');
}

static bool
hasSouthNeighbor(size_t row, size_t col, const std::vector<std::string>& lines, const char& c)
{
    const auto rows = lines.size();

    if (row == rows - 1)
        return false;

    const auto& co = lines[row + 1][col];

    return (c == '|' || c == 'F' || c == '7') && (co == '|' || co == 'L' || co == 'J');
}

static bool
hasWestNeighbor(size_t row, size_t col, const std::vector<std::string>& lines, const char& c)
{
    if (col == 0)
        return false;

    const auto& co = lines[row][col - 1];

    return (c == '-' || c == '7' || c == 'J') && (co == '-' || co == 'F' || co == 'L');
}

static std::vector<NodePtr>
findNeighbors(size_t row, size_t column, const std::vector<std::string>& lines)
{
    std::vector<NodePtr> nodes;

    if (hasNorthNeighbor(row, column, lines, lines[row][column]))
        nodes.push_back(std::make_shared<Node>(row - 1, column));

    if (hasEastNeighbor(row, column, lines, lines[row][column]))
        nodes.push_back(std::make_shared<Node>(row, column + 1));

    if (hasSouthNeighbor(row, column, lines, lines[row][column]))
        nodes.push_back(std::make_shared<Node>(row + 1, column));

    if (hasWestNeighbor(row, column, lines, lines[row][column]))
        nodes.push_back(std::make_shared<Node>(row, column - 1));

    return nodes;
}

static std::optional<size_t> farthestDistance(Graph& unvisited, const NodePtr& e)
{
    Graph visited;

    while (!unvisited.empty())
    {
        const NodePtr node = *unvisited.cbegin();

        if (node->distance == -1ul)
            break;

        for (auto& neighbor : node->neighbors)
        {
            auto it = std::find(unvisited.cbegin(), unvisited.cend(), neighbor);
            if (it == unvisited.cend())
                continue;

            neighbor->distance = node->distance + 1;
            unvisited.erase(it);
            unvisited.insert(neighbor);
        }

        unvisited.erase(unvisited.cbegin());
        visited.insert(node);
    }

    if (unvisited.contains(e))
        return {};

    if (!visited.empty())
        return e->distance / 2;

    return {};
}

static void resetDistances(const Graph& graph)
{
    for (const auto& node : graph)
        node->distance = -1;
}

Node::Node(size_t row, size_t column)
    : row(row)
    , column(column)
{
}

NodePtr findStart(const std::vector<std::string>& lines)
{
    const size_t linesCount = lines.size();
    for (size_t row = 0; row != linesCount; ++row)
    {
        const auto& line = lines[row];
        const auto  col = line.find('S');

        if (col != line.npos)
            return std::make_shared<Node>(row, col);
    }

    // shouldn't happen
    return {};
}

std::vector<PotentialStart> potentialStarts(const std::vector<std::string>& lines,
                                            const Graph&                    graph)
{
    std::vector<PotentialStart> starts;

    const NodePtr start = findStart(lines);

    auto addPotentialStart = [&](size_t row1, size_t col1, size_t row2, size_t col2)
    {
        auto findNeighbor = [&](size_t row, size_t col) -> NodePtr
        {
            auto it = std::find_if(graph.cbegin(),
                                   graph.cend(),
                                   [&](const auto& node)
                                   { return node->row == row && node->column == col; });
            if (it != graph.cend())
                return *it;

            return {};
        };

        NodePtr firstNeighbor = findNeighbor(row1, col1);
        NodePtr secondNeighbor = findNeighbor(row2, col2);

        // shouldn't happen
        if (!firstNeighbor || !secondNeighbor)
            return;

        auto potStart = std::make_shared<Node>(start->row, start->column);
        potStart->distance = 0;
        potStart->neighbors.push_back(firstNeighbor);
        firstNeighbor->neighbors.push_back(potStart);

        auto potEnd = std::make_shared<Node>(start->row, start->column);
        potEnd->neighbors.push_back(secondNeighbor);
        secondNeighbor->neighbors.push_back(potEnd);

        starts.push_back(std::make_tuple(potStart, potEnd));
    };

    const auto row = start->row;
    const auto col = start->column;

    char c = {};

    auto hasNorth = [&]() { return hasNorthNeighbor(row, col, lines, c); };
    auto hasSouth = [&]() { return hasSouthNeighbor(row, col, lines, c); };
    auto hasEast = [&]() { return hasEastNeighbor(row, col, lines, c); };
    auto hasWest = [&]() { return hasWestNeighbor(row, col, lines, c); };

    c = '-';
    if (hasEast() && hasWest())
        addPotentialStart(row, col - 1, row, col - 2);

    c = '|';
    if (hasNorth() && hasSouth())
        addPotentialStart(row - 1, col, row + 1, col);

    c = 'L';
    if (hasNorth() && hasEast())
        addPotentialStart(row - 1, col, row, col + 1);

    c = 'J';
    if (hasNorth() && hasWest())
        addPotentialStart(row - 1, col, row, col - 1);

    c = '7';
    if (hasSouth() && hasWest())
        addPotentialStart(row + 1, col, row, col - 1);

    c = 'F';
    if (hasSouth() && hasEast())
        addPotentialStart(row + 1, col, row, col + 1);

    return starts;
}

bool Comparator::operator()(const NodePtr& node1, const NodePtr& node2) const
{
    if (node1->distance == node2->distance)
    {
        if (node1->row == node2->row)
            return node1->column < node2->column;

        return node1->row < node2->row;
    }

    return node1->distance < node2->distance;
}

static NodePtr copyNode(const NodePtr& other, Graph& graph)
{
    const auto node = std::make_shared<Node>(other->row, other->column);
    node->distance = other->distance;

    const auto [it, success] = graph.insert(node);
    if (!success)
        return *it;

    for (const auto& otherNeighbor : other->neighbors)
        node->neighbors.push_back(copyNode(otherNeighbor, graph));

    return *it;
}

Graph cloneGraph(const Graph& other)
{
    Graph graph;

    for (const auto& node : other)
        copyNode(node, graph);

    return graph;
}

Graph convertToGraph(const std::vector<std::string>& lines)
{
    const auto rows = lines.size();
    const auto columns = lines.front().size();

    Graph graph;

    for (size_t row = 0; row != rows; ++row)
    {
        for (size_t column = 0; column != columns; ++column)
        {
            const auto& c = lines[row][column];
            if (isDot(c) || isStart(c))
                continue;

            const auto& neighbors = findNeighbors(row, column, lines);
            if (neighbors.empty())
                continue;

            auto [nodeIt, success0] = graph.insert(std::make_shared<Node>(row, column));
            auto& nodeNeighbors = const_cast<std::vector<NodePtr>&>(nodeIt->get()->neighbors);

            for (const auto& neighbor : neighbors)
            {
                const auto [neighborIt, success1] = graph.insert(neighbor);
                nodeNeighbors.push_back(*neighborIt);
            }
        }
    }

    return graph;
}

std::tuple<size_t, NodePtr> farthestDistance(const char* fileName)
{
    const auto lines = readFile(fileName);

    const Graph graph = convertToGraph(lines);

    const std::vector<PotentialStart> starts = potentialStarts(lines, graph);

    size_t distance = {};
    NodePtr endNode = nullptr;

    for (const auto& [s, e] : starts)
    {
        resetDistances(graph);

        Graph sGraph = cloneGraph(graph);
        copyNode(s, sGraph);
        const auto end = copyNode(e, sGraph);

        if (const auto d = farthestDistance(sGraph, end))
        {
            if (d < distance)
                continue;

            distance = *d;
            endNode = end;
        }
    }

    return std::make_tuple(distance, endNode);
}

static std::tuple<Coords, Coords> boundingBox(const Graph& loop)
{
    const size_t maxRow =
        (*std::max_element(loop.cbegin(),
                           loop.cend(),
                           [](const auto& co1, const auto& co2) { return co1->row < co2->row; }))
            ->row;

    const size_t maxCol = (*std::max_element(loop.cbegin(),
                                             loop.cend(),
                                             [](const auto& co1, const auto& co2)
                                             { return co1->column < co2->column; }))
                              ->column;

    const size_t minRow =
        (*std::min_element(loop.cbegin(),
                           loop.cend(),
                           [](const auto& co1, const auto& co2) { return co1->row < co2->row; }))
            ->row;

    const size_t minCol = (*std::min_element(loop.cbegin(),
                                             loop.cend(),
                                             [](const auto& co1, const auto& co2)
                                             { return co1->column < co2->column; }))
                              ->column;

    return std::make_tuple(Coords(minRow, minCol), Coords(maxRow, maxCol));
}

size_t innerTiles(const char* fileName)
{
    const auto [distance, endNode] = farthestDistance(fileName);

    const auto loop = getLoop(endNode);

    const auto [leftTop, rightBottom] = boundingBox(loop);

    auto flipInLoop = [&](const Coords& co, bool& inLoop)
    {
        const auto it =
            std::find_if(loop.cbegin(),
                         loop.cend(),
                         [&](const auto& n) { return n->row == co.row && n->column == co.column; });

        if (it == loop.cend())
            return false;

        const NodePtr node = *it;

        if (std::any_of(node->neighbors.cbegin(),
                        node->neighbors.cend(),
                        [&](const auto& n)
                        { return n->row - 1 == co.row && n->column == node->column; }))
        {
            inLoop = !inLoop;
        }

        return true;
    };

    size_t tiles = 0;

    for (size_t row = leftTop.row; row < rightBottom.row; ++row)
    {
        bool inLoop = false;

        for (size_t col = leftTop.column; col < rightBottom.column; ++col)
        {
            if (flipInLoop({row, col}, inLoop))
                continue;

            if (inLoop)
                tiles++;
        }
    }

    return tiles;
}

Graph getLoop(const NodePtr& endNode)
{
    Graph loop;

    const auto end = copyNode(endNode, loop);

    loop.erase(loop.cbegin());

    const auto firstAfterStart =
        *std::find_if(loop.cbegin(), loop.cend(), [&](const auto& n) { return n->distance == 1; });

    end->neighbors.push_back(firstAfterStart);

    const auto it =
        std::find_if(firstAfterStart->neighbors.cbegin(),
                     firstAfterStart->neighbors.cend(),
                     [&](const auto& n) { return n->row == end->row && n->column == end->column; });
    firstAfterStart->neighbors.erase(it);
    firstAfterStart->neighbors.push_back(end);

    return loop;
}

} // namespace core
