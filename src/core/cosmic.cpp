#include <set>

#include "cosmic.h"
#include "utils.h"

namespace core
{

static inline bool isGalaxy(const char& c)
{
    return c == '#';
}

Positions expandSpace(const char* fileName)
{
    const auto lines = readFile(fileName);

    const auto rows = lines.size();
    const auto cols = lines.front().size();

    const Positions galaxies = getGalaxies(lines);

    std::set<int> galaxyRows;
    std::set<int> galaxyCols;

    for (const auto& galaxy : galaxies)
    {
        galaxyRows.insert(galaxy.x);
        galaxyCols.insert(galaxy.y);
    }

    Positions correctedGalaxies = galaxies;

    int lastRow = 0;

    for (const auto& row : galaxyRows)
    {
        const auto delta = row - lastRow - 1;
        lastRow = row;

        if (delta <= 0)
            continue;

        for (auto it = galaxies.begin(); it != galaxies.end(); ++it)
        {
            if (it->x < row)
                continue;

            auto& correctedGalaxy = correctedGalaxies[std::distance(galaxies.cbegin(), it)];
            correctedGalaxy.x += delta;
        }
    }

    int lastCol = 0;

    for (const auto& col : galaxyCols)
    {
        const auto delta = col - lastCol - 1;
        lastCol = col;

        if (delta <= 0)
            continue;

        for (auto it = galaxies.begin(); it != galaxies.end(); ++it)
        {
            if (it->y < col)
                continue;

            auto& correctedGalaxy = correctedGalaxies[std::distance(galaxies.cbegin(), it)];
            correctedGalaxy.y += delta;
        }
    }

    return correctedGalaxies;
}

Positions getGalaxies(const Lines& lines)
{
    Positions positions;

    const int rows = static_cast<int>(lines.size());
    const int cols = static_cast<int>(lines.front().size());

    for (int x = 0; x != rows; ++x)
    {
        for (int y = 0; y != cols; ++y)
        {
            if (isGalaxy(lines[x][y]))
                positions.push_back({x, y});
        }
    }

    return positions;
}

std::vector<size_t> distances(const char* fileName)
{
    std::vector<size_t> distances;

    const Positions galaxies = expandSpace(fileName);

    const size_t count = galaxies.size();
    for (size_t i = 0; i < count; ++i)
    {
        const auto galaxy1 = galaxies[i];

        for (size_t j = i + 1; j < count; ++j)
        {
            const auto galaxy2 = galaxies[j];
            distances.push_back(std::abs(galaxy1.x - galaxy2.x) + std::abs(galaxy1.y - galaxy2.y));
        }
    }

    return distances;
}

} // namespace core
