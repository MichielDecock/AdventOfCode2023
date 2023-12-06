#include <string>

#include "include/cubes_game.h"
#include "include/utils.h"

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

std::vector<size_t> powerGameIDs(const char* fileName)
{
    const auto lines = core::readFile(fileName, {':', ';', ','});

    std::vector<size_t> ids;

    size_t currentRed = 0;
    size_t currentGreen = 0;
    size_t currentBlue = 0;

    bool skip = true;

    for (const auto& line : lines)
    {
        if (line.find("Game") != line.npos)
        {
            if (!skip)
            {
                const size_t power = currentRed * currentGreen * currentBlue;
                ids.push_back(power);
            }

            currentRed = 0;
            currentGreen = 0;
            currentBlue = 0;

            skip = false;
        }

        else if (const auto pos = line.find("red"); pos != line.npos)
        {
            currentRed =
                std::max(currentRed, static_cast<size_t>(std::stoi(line.substr(0, pos - 1))));
        }

        else if (const auto pos = line.find("green"); pos != line.npos)
        {
            currentGreen =
                std::max(currentGreen, static_cast<size_t>(std::stoi(line.substr(0, pos - 1))));
        }

        else if (const auto pos = line.find("blue"); pos != line.npos)
        {
            currentBlue =
                std::max(currentBlue, static_cast<size_t>(std::stoi(line.substr(0, pos - 1))));
        }
    }

    const size_t power = currentRed * currentGreen * currentBlue;
    ids.push_back(power);

    return ids;
}

} // namespace core
