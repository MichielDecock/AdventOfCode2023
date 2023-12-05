#include <string>

#include "include/core_cubes_game.h"
#include "include/core_utils.h"

namespace core
{

std::vector<size_t>
validGameIDs(const char* fileName, size_t maxRed, size_t maxGreen, size_t maxBlue)
{
    const auto lines = core::readFile(fileName, {':', ';', ','});

    std::vector<size_t> ids;

    std::optional<size_t> currentID;

    for (const auto& line : lines)
    {
        if (line.find("Game") != line.npos)
        {
            if (currentID)
                ids.push_back(*currentID);

            currentID = std::stoi(line.substr(5));
        }

        else if (!currentID)
            continue;

        else if (const auto pos = line.find("red"); pos != line.npos)
        {
            if (std::stoi(line.substr(0, pos - 1)) > maxRed)
                currentID = std::nullopt;
        }

        else if (const auto pos = line.find("green"); pos != line.npos)
        {
            if (std::stoi(line.substr(0, pos - 1)) > maxGreen)
                currentID = std::nullopt;
        }

        else if (const auto pos = line.find("blue"); pos != line.npos)
        {
            if (std::stoi(line.substr(0, pos - 1)) > maxBlue)
                currentID = std::nullopt;
        }
    }

    if (currentID)
        ids.push_back(*currentID);

    return ids;
}

} // namespace core
