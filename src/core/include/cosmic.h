#pragma once
#include <string>
#include <vector>

namespace core
{

struct Position
{
    Position(int x, int y)
        : x(x)
        , y(y)
    {
    }

    int x = 0;
    int y = 0;
};

using Positions = std::vector<Position>;
using Lines = std::vector<std::string>;

Positions expandSpace(const char* fileName, size_t factor);

Positions getGalaxies(const Lines& lines);

std::vector<size_t> distances(const char* fileName, size_t factor);

} // namespace core
