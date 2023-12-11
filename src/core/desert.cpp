#include <numeric>

#include "desert.h"
#include "utils.h"

namespace core
{

static inline void ltrim(std::string& s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char ch) { return ch != '('; }));
}

static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return ch != ')'; }).base(),
            s.end());
}

static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

static std::optional<Node> convertToNode(const std::string&              string,
                                         const std::vector<std::string>& nodes)
{
    const auto found = std::find(nodes.cbegin(), nodes.cend(), string);
    if (found != nodes.cend())
        return std::distance(nodes.cbegin(), found);

    return {};
}

std::tuple<Instructions, Paths, Nodes, Nodes> convertInput(const char* filePath)
{
    auto lines = readFile(filePath, {'=', ','});

    Instructions instructions;
    for (const auto& c : lines.front())
        instructions.push_back(c == 'R');

    lines.erase(lines.begin());

    for (auto& line : lines)
        trim(line);

    std::vector<std::string> nodes;
    std::vector<std::string> rawPaths;

    const size_t count = lines.size();
    for (size_t i = 0; i != count; ++i)
    {
        const auto& line = lines[i];
        if (i % 3 == 0)
            nodes.push_back(line);
        else
            rawPaths.push_back(line);
    }

    Nodes starts;
    Nodes targets;

    const size_t countNodes = nodes.size();
    for (size_t i = 0; i != countNodes; ++i)
    {
        const auto& node = nodes[i];
        if (node.ends_with('A'))
            starts.push_back(*convertToNode(node, nodes));
        else if (node.ends_with('Z'))
            targets.push_back(*convertToNode(node, nodes));
    }

    Paths paths;
    Path  curPath;

    const size_t countRawPaths = rawPaths.size();
    for (size_t i = 0; i != countRawPaths; ++i)
    {
        const auto node = convertToNode(rawPaths[i], nodes);
        if (!node)
            continue;

        if (i % 2 == 0)
        {
            curPath.left = *node;
            continue;
        }

        curPath.right = *node;
        paths.push_back(curPath);
    }

    return std::make_tuple(instructions, paths, starts, targets);
}

Steps steps(const char* filePath)
{
    const auto [instructions, paths, starts, targets] = convertInput(filePath);
    const auto instructionsCount = instructions.size();

    Steps                               steps = 0;
    std::array<std::optional<Steps>, 6> hits{};
    Nodes                               curNodes = starts;

    auto hitAllTargetsAtLeastOnce = [&targets, &curNodes, &hits, &steps]()
    {
        for (size_t i = 0; i != curNodes.size(); ++i)
        {
            const auto& node = curNodes[i];
            if (std::find(targets.cbegin(), targets.cend(), node) != targets.cend())
            {
                if (!hits[i])
                    hits[i] = steps;
            }
        }

        return std::find(hits.cbegin(), hits.cend(), std::nullopt) == hits.cend();
    };

    while (!hitAllTargetsAtLeastOnce())
    {
        const bool curInstruction = instructions[steps % instructionsCount];

        for (auto& node : curNodes)
        {
            const auto curPath = paths[node];
            node = curInstruction ? curPath.right : curPath.left;
        }

        steps++;
    }

    Steps lcm = 1;
    for (const auto& frequency : hits)
        lcm = std::lcm(lcm, *frequency);

    return lcm;
}

} // namespace core
