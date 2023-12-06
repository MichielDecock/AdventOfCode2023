#include <fstream>
#include <numeric>
#include <sstream>

#include "include/utils.h"

namespace
{

std::vector<std::string> splitLine(const std::string& line, const std::vector<char>& delimiters)
{
    std::stringstream sstream(line);
    std::string       chunk;

    std::vector<std::string> chunks;

    while (std::getline(sstream, chunk, delimiters.front()))
    {
        if (chunk.empty())
            continue;

        if (delimiters.size() <= 1)
        {
            chunks.push_back(chunk);
            continue;
        }

        const std::vector<char> otherDelimiters(delimiters.cbegin() + 1, delimiters.cend());

        const auto subChunks = splitLine(chunk, otherDelimiters);
        chunks.insert(chunks.end(), subChunks.cbegin(), subChunks.cend());
    }

    return chunks;
}

} // namespace

namespace core
{

std::vector<std::string> readFile(const char* fileName, const std::vector<char>& delimiters)
{
    std::vector<std::string> lines;

    std::fstream fstream;
    fstream.open(std::string(CMAKE_SOURCE_DIR) + "/" + fileName);

    std::string line;
    while (std::getline(fstream, line))
    {
        if (line.empty())
            continue;

        if (delimiters.empty())
        {
            lines.push_back(line);
            continue;
        }

        const auto chunks = splitLine(line, delimiters);
        lines.insert(lines.end(), chunks.begin(), chunks.end());
    }

    return lines;
}

std::size_t sum(const std::vector<size_t>& numbers)
{
    return std::accumulate(numbers.cbegin(), numbers.cend(), 0ul);
}

} // namespace core
