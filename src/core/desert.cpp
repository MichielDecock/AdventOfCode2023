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

std::tuple<Instructions, Paths, Node, Node> convertInput(const char* filePath)
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
        if (i % 3 == 0)
            nodes.push_back(lines[i]);
        else
            rawPaths.push_back(lines[i]);
    }

    const auto start = convertToNode("AAA", nodes);
    const auto target = convertToNode("ZZZ", nodes);

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

    return std::make_tuple(instructions, paths, *start, *target);
}

Steps steps(const char* filePath)
{
    const auto [instructions, paths, start, target] = convertInput(filePath);
    const auto instructionsCount = instructions.size();

    Steps steps = 0;
    Node  curNode = start;

    while (curNode != target)
    {
        const bool curInstruction = instructions[steps % instructionsCount];
        const auto curPath = paths[curNode];

        curNode = curInstruction ? curPath.right : curPath.left;
        steps++;
    }

    return steps;
}

} // namespace core
